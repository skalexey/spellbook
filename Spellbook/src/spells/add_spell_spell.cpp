#include <unordered_map>
#include <vl.h>
#include <utils/Log.h>
#include "spells/add_spell_spell.h"
#include "generated/content.h"
#include "generated/types.h"
#include "spell_context.h"

LOG_PREFIX("[add_spell_spell]: ");
LOG_POSTFIX("\n");

namespace spl
{
	const std::unordered_map<int, std::string> add_spell_spell::s_retmessage = create_retcode_message_map();
	
	std::unordered_map<int, std::string> add_spell_spell::create_retcode_message_map()
	{
		std::unordered_map<int, std::string> result;
		result[int(base::erc::OK)] = "Casted successfully";
		result[erc::ALREADY_EXISTS] = "A spell with this alias already exists";
		result[erc::DATA_ERROR] = "Data error";
		result[erc::OPTION_MISSED] = "Option missed";
		result[erc::STORE_ERROR] = "Store error";
		return result;
	}

	const std::string& add_spell_spell::retmessage(int code)
	{
		auto it = s_retmessage.find(code);
		if (it != s_retmessage.end())
			return it->second;
		static const std::string empty_string;
		return empty_string;
	}

	// Static spell registrator
	const add_spell_spell::initializer add_spell_spell::m_initializer("add-spell");
	int add_spell_spell::cast(const option_list& args, spl::context& ctx)
	{
		int ret = base::cast(args, ctx);
		if (ret != base::erc::OK)
			return ret;
		auto spells = ctx.get_content_data().get_spellbook().get_spells();
		auto& alias = get_alias();
		auto& registry = spells.get_registry();
		auto& registry_data = registry.get_data()->AsObject();
		// Create a new spell object
		vl::Object obj;
		std::string new_spell_alias;
		if (auto types = ctx.get_types_data())
		{
			auto spell_class = types.get_Spell();
			obj.SetPrototype(spell_class.get_data()->AsObject());
			auto& options = get_data().get_options().get_registry();
			// spell_class.get_data()->AsObject().ForeachProp([&](auto& n, auto& v) {
			options.get_data()->AsObject().ForeachProp([&](auto& n, auto& v) {
				auto on_option_missed = [&] {
					set_last_spell_msg(ctx, "option '" + n + "' is missed");
					ret = erc::OPTION_MISSED;
					return false;
				};
				auto it = args.find(n);
				if (it != args.end())
				{
					auto& arg = (*it).second;
					auto& arg_val = arg.value();
					if (arg_val.empty())
						if (!arg.has_data_own("default_value"))
							return on_option_missed();

					if (n == "alias")
					{
						new_spell_alias = arg_val;
						if (registry_data.Has(new_spell_alias))
						{
							set_last_spell_msg(ctx, retmessage(erc::ALREADY_EXISTS));
							ret = erc::ALREADY_EXISTS;
							return false;
						}
					}
					obj.Set(n, arg_val);
				}
				else if (n != "options") // Spell with no options is valid
				{
					auto opt = cppgen::Option(v);
					if (!opt.has_data_own("default_value"))
						return on_option_missed();
				}
				return true;
			});
			if (ret != base::erc::OK)
				return ret;

			registry_data.Set(new_spell_alias, obj);
		}
		else
		{
			set_last_spell_msg(ctx, "No 'types' field in the DB has been found");
			return ret = erc::DATA_ERROR;
		}
		spells.list().Add(vl::MakePtr(new_spell_alias));
		if (!ctx.db().Store("", {true}))
		{
			set_last_spell_msg(ctx, "can't store the Spellbook");
			return ret = erc::STORE_ERROR;
		}
		return ret;
	}

}
