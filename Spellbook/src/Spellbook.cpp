// Spellbook.cpp : Defines the entry point for the application.
//

// Participants
//	* parser
//		* parse(string)
//	* spell_expression
//		* cast() / run / invoke / call
//		* alias
//		* options
//	* context
//		* spell_list
//

#include <optional>
#include <thread>
#include <memory>
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <string>
#include <exception>
#include <vl_fwd.h>
#include <utils/Log.h>
#include <utils/io_utils.h>
#include <utils/file_utils.h>
#include <DMBCore.h>
#include "generated/Spell.h"
#include "generated/Option.h"
#include "spell_parser.h"
#include "spell_expression.h"
#include "spell_context.h"
#include "spell_factory.h"
#include "spell_options.h"
#include "spell.h"
#include "Spellbook.h"
#ifdef LOG_ON
LOG_TITLE("Spellbook")
SET_LOG_DEBUG(true)
#endif

#define COUT(msg1) std::cout << msg1
#define MSG(msg1) COUT(msg1 << '\n')

namespace fs = std::filesystem;

const fs::path cfg_path = fs::temp_directory_path() / "sb_config.json";
const fs::path def_cfg_path = fs::temp_directory_path() / "spellbook_default.json";

bool request_argument(cppgen::Option& opt)
{
	COUT("\t" << opt.title());
	utils::input::register_command("~skip");
	bool is_optional = opt.has_data_own("default_value");
	if (is_optional)
		COUT(" (optional)");
	COUT(": ");
	std::string val;
	while (val.empty())
	{
		utils::input::getline(std::cin, val);
		if (!utils::input::last_getline_valid)
			if (utils::input::last_command == "~skip")
				return false;
		if (val.empty())
		{
			if (is_optional)
			{
				if (utils::input::ask_user("No value? Sure?"))
					break;
			}
			else
			{
				MSG("This is a required option. It should be set (or type '~skip' to stop casting)");
			}
		}
	}
	utils::input::unregister_command("~skip");
	opt.set_value(val);
	// TODO: check the option validity
	return true;
}

bool request_argument(spl::spell_expression& ex, cppgen::Option& opt)
{
	auto& alias = opt.alias();
	auto& args = ex.args();
	auto it = args.find(alias);
	if (it == args.end())
		return request_argument(args.add(alias, cppgen::Option(opt.get_data()->Copy())));
	auto& arg = (*it).second;
	if (arg.value().empty()) // The argument has not been given, so stop the process
		return request_argument(arg);
	return true;
}

bool request_missed_args(spl::spell_expression& ex, spl::context& ctx)
{
	return ex.iterate_options([&](auto& ex, auto& opt) -> bool {
		if (ex.is_option_missed(opt) || ctx.ask_optional())
			return request_argument(ex, opt);
		return true;
	});
}

std::optional<int> load_sb(spl::context& ctx)
{
	utils::input::register_command("~skip");
	
	const std::string sb_fname = "spellbook.json";

	dmb::Model cfg_model;
	if (!cfg_model.Load(cfg_path.string()))
		cfg_model.Store(cfg_path.string(), { true });

	const std::string sb_dir_field_name = "sb_dir";

	auto update_sb_dir = [&](const std::string& new_dir)
	{
		auto& data = cfg_model.GetContent().GetData();
		if (fs::path(new_dir) == fs::temp_directory_path())
			data.Set(sb_dir_field_name, "");
		else
		{
			if (data.Get(sb_dir_field_name).AsString().Val() != new_dir)
			{
				data.Set(sb_dir_field_name, new_dir);
				cfg_model.Store(cfg_path.string(), { true });
			}
		}
	};

	auto sb_dir = cfg_model.GetContent().Get(sb_dir_field_name).AsString().Val();
	fs::path sb_path = sb_dir.empty() ? fs::temp_directory_path() / sb_fname : fs::path(sb_dir) / sb_fname;
	bool created = utils::file::exists(sb_path);
	while (!created)
	{
		std::string msg1, msg2;
		if (!sb_dir.empty())
		{
			msg1 = "Can't find your spellbook in the directory provided by you: '"
				+ sb_dir + "'. Would you like to provide a custom path? "
				"Otherwise it will be created in the current directory.";
			msg2 = "Enter spellbook location directory or type 'skip' to use the "
				"current directory or 'exit' to close the application";
		}
		else
		{
			msg1 = "Where is your spellbook?\nWould you like to specify a custom path? "
				"Otherwise we will keep it in the app data directory located here:\n"
				+ fs::temp_directory_path().string();
			msg2 = "Enter spellbook location directory or type 'skip' to use the "
				"default folder or 'exit' to close the application";
		}
		if (utils::input::ask_user(msg1))
		{
			fs::path entered_path;
			do
			{
				COUT(msg2 << "\n > ");
				std::string dir;

				while (dir.empty() && utils::input::last_getline_valid)
				{
					if (!utils::input::getline(std::cin, dir))
					{
						LOG_ERROR("Input stream failure");
						return 4;
					}
				}

				if (!utils::input::last_getline_valid)
				{
					if (utils::input::last_command == "~exit")
						return 0;
					else if (utils::input::last_command == "~skip")
						break;
				}
				auto p = fs::path(dir);
				if (!utils::file::dir_exists(p))
				{
					if (utils::input::ask_user("There is no directory in the provided path. "
						"Would you use temporary directory instead? "
						"It is located here:\n" + fs::temp_directory_path().string())
						)
					{
						entered_path = fs::temp_directory_path();
						sb_dir = "";
					}
				}
				else
					sb_dir = (entered_path = p).string();
			} while (entered_path.empty());
			sb_path = entered_path / sb_fname;
			// Load or create DB
				//MSG("Sorry, but without a spellbook you can't cast any spell. Come back when you are ready.");
		}
		update_sb_dir(sb_dir);
		if (!utils::file::exists(sb_path))
		{
			if (auto erc = utils::file::copy_file(def_cfg_path, sb_path))
			{	// No default spellbook config found
				if (erc == 3)
				{
					MSG("Can't create spellbook in the location '" << sb_path <<
						"'. Reason: '" << utils::file::last_error() << "'"
					);
				}
				else
					MSG("Unexpected error (code " << (erc *= 10) << ")");
				return erc;
			}
		}
		created = true;
		MSG("Your spellbook is created at the path '" << fs::absolute(sb_path).string() << "'");
	}

	if (!ctx.load_spells(sb_path.string()))
	{
		MSG("Can't load your spellbook located at '" << sb_path.string() << "'");
		return 3;
	}
	return std::nullopt;
}

int main(int argc, char const* argv[])
{
	LOG("=== Spellbook Project ===\n");
	utils::input::register_command("~exit", [] {
		std::terminate();
		return false;
	});
	spl::context ctx;
	auto ret = load_sb(ctx);
	if (ret)
		return ret.value();
	
	utils::input::unregister_command("~skip");

	auto process_ex_args = [&](const spl::spell_expression_ptr& ex) {
		if (ex->has_missed_args(ctx))
			if (!request_missed_args(*ex, ctx))
			{
				MSG("	Some arguments has been not provided. Can't cast the spell");
				return false;
			}
		return true;
	};

	auto on_cant_parse = [] {
		MSG("	Can't figure out what you've said");
	};

	int result = -1;

	auto on_cast = [&] {
		if (result == 0)
			MSG("CASTED!");
		else
		{
			if (!ctx.last_spell_msg().empty())
				MSG("Error during casting: '" << ctx.last_spell_msg() << "' (code " << result << ")");
			else
				LOG_DEBUG("Error during casting: code " << result);
		}
	};

	if (argc < 2)
	{
		ctx.set_ask_optional(true);
		std::string s;
		while (true)
		{
			COUT("Your spell: ");
			std::getline(std::cin, s);
			if (s == "~exit")
				break;
			MSG("");
			//		MSG(" parse string '" << s);
			if (s.empty())
				continue;
			if (auto spell_ex = spl::parser::parse(s, ctx))
			{
				if (!process_ex_args(spell_ex))
					continue;
				result = spell_ex->execute(ctx);
			}
			else
				on_cant_parse();
			s.clear();

			on_cast();
		}
	}
	else
	{
		if (auto spell_ex = spl::parser::parse(argc, argv, ctx))
		{
			if (process_ex_args(spell_ex))
				result = spell_ex->execute(ctx);
		}
		else
			on_cant_parse();

		on_cast();
	}
	
	return 0;
}
