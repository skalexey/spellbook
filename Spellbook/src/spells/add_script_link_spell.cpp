#include <filesystem>
#include <unordered_map>
#include <vl.h>
#include <utils/log.h>
#include <DMBCore.h>
#include "spells/add_script_link_spell.h"
#include "spells/script_link_spell.h"
#include "generated/content.h"
#include "generated/types.h"
#include "spell_context.h"

#ifdef LOG_ON
LOG_PREFIX("[add_script_link_spell]: ");
LOG_POSTFIX("\n");
#endif

namespace fs = std::filesystem;

namespace spl
{
	const std::unordered_map<int, std::string> add_script_link_spell::s_retmessage = create_retcode_message_map();
	
	std::unordered_map<int, std::string> add_script_link_spell::create_retcode_message_map()
	{
		std::unordered_map<int, std::string> result;
		result[int(erc::REGISTRY_ERROR)] = "Can't find spell data after its successfull creation";
		return result;
	}

	const std::string& add_script_link_spell::retmessage(int code)
	{
		auto it = s_retmessage.find(code);
		if (it != s_retmessage.end())
			return it->second;
		static const std::string empty_string;
		return empty_string;
	}

	// Static spell registrator
	const add_script_link_spell::initializer add_script_link_spell::m_initializer(
		"add-script-spell", [] (spl::context& ctx) {
			auto content = ctx.get_content_data();
			auto content_data = content.get_data()->AsObject();
			if (!content_data.Has("script_links"))
				return;
			auto links_list = content.get_data("script_links").AsList();
			for (int i = 0; i < links_list.Size(); i++)
				spell_factory::register_spell<script_link_spell>(links_list.At(i).AsString().Val());
		});

	int add_script_link_spell::cast(const option_list& args, spl::context& ctx)
	{
		// Preprocess arguments logic
		auto it_path = args.find("path");
		if (it_path == args.end())
			return base::erc::OPTION_MISSED;

		auto& path = args.get_value("path").value();

		std::string new_spell_alias;
		auto alias_it = args.find("alias");
		if (alias_it != args.end())
			new_spell_alias = (*alias_it).second.value();

		auto args_copy = args;
		auto content = ctx.get_content_data();
		auto spells = content.get_spellbook().get_spells();
		if (new_spell_alias.empty())
		{
			fs::path p(path);
			if (!p.empty())
				new_spell_alias = p.stem().string();
			else
				new_spell_alias = path;
			auto& alias_opt = alias_it == args.end() ?
				args_copy.add("alias", cppgen::Option(get_data().get_options().get_registry().get_data("alias")))
				: (*alias_it).second;
			alias_opt.set_value(new_spell_alias);
		}

		// Add the spell with basic data using base class method
		ctx.set_store_allowed(false);
		int ret = base::cast(args_copy, ctx);
		ctx.set_store_allowed(true);
		if (ret != spell::erc::OK && ret != base::erc::STORE_ERROR)
			return ret;
		
		// Get the newly created data from the registry
		auto& registry = spells.get_registry();
		auto& registry_data = registry.get_data()->AsObject();
		
		if (!registry_data.Has(new_spell_alias))
			return erc::REGISTRY_ERROR;

		// Add path field to the created spell
		auto& new_spell_data = registry_data.Get(new_spell_alias).AsObject();
		new_spell_data.Set("path", args_copy.get_value("path").value());

		// Add spell to script_links registry
		auto content_data = content.get_data()->AsObject();
		auto& script_links_data = (content_data.Has("script_links") ? 
			content_data.Get("script_links") : content_data.Set("script_links", vl::List())
			).AsList();
		script_links_data.Add(new_spell_alias);

		// Store DB
		if (!ctx.db().Store("", { true }))
		{
			set_last_spell_msg(ctx, "can't store the Spellbook");
			return base::erc::STORE_ERROR;
		}

		// Register the spell so you can use it in this session just right after creation
		spell_factory::register_spell<script_link_spell>(new_spell_alias);

		return ret;
	}

}
