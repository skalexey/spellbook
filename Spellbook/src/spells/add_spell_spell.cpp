#include <unordered_map>
#include <vl.h>
#include <utils/Log.h>
#include "spells/add_spell_spell.h"
#include "generated/content.h"
#include "generated/types.h"
#include "spell_context.h"
#ifdef LOG_ON
	LOG_TITLE("add_spell_spell")
	LOG_STREAM([]() -> std::ostream& { return std::cout; })
	SET_LOG_DEBUG(true)
#endif

namespace spl
{
	const std::unordered_map<int, std::string> add_spell_spell::s_retmessage = create_retcode_message_map();
	
	std::unordered_map<int, std::string> add_spell_spell::create_retcode_message_map()
	{
		std::unordered_map<int, std::string> result;
		result[int(retcode::OK)] = "Casted successfully";
		result[retcode::ALREADY_EXISTS] = "A spell with this alias already exists";
		result[retcode::DATA_ERROR] = "Data error";
		result[retcode::OPTION_MISSED] = "Option missed";
		result[retcode::STORE_ERROR] = "Store error";
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
			auto ret = retcode::OK;
			spell_class.get_data()->AsObject().ForeachProp([&](auto& n, auto& v) {
				auto it = args.find(n);
				if (it != args.end())
				{
					auto& opt_val = (*it).second.value();
					if (n == "alias")
					{
						new_spell_alias = opt_val;
						if (registry_data.Has(new_spell_alias))
						{
							LOCAL_LOG("Error occured during casting a spell '" << alias << "': "
									  << retmessage(retcode::ALREADY_EXISTS));
							ret = retcode::ALREADY_EXISTS;
							return false;
						}
					}
					obj.Set(n, opt_val);
				}
				else if (n != "options") // Spell with no options is valid
				{
					LOCAL_LOG("Error occured during casting a spell '" << alias
							  << "': option '" << n << "' is missed");
					ret = retcode::OPTION_MISSED;
					return false;
				}
				return true;
			});
			if (ret != retcode::OK)
				return ret;

			registry_data.Set(new_spell_alias, obj);
		}
		else
		{
			LOCAL_LOG("No 'types' field in the DB has been found");
			return retcode::DATA_ERROR;
		}
		spells.list().Add(vl::MakePtr(new_spell_alias));
		if (!ctx.db().Store("", {true}))
		{
			LOCAL_LOG("Error occured during casting a spell '" << alias << "': can't store the Spellbook");
			return retcode::STORE_ERROR;
		}
		LOCAL_LOG("Spell '" << alias << "' CASTED!");
		return retcode::OK;
	}

}
