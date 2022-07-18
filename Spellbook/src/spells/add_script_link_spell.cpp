#include <unordered_map>
#include <vl.h>
#include <utils/Log.h>
#include <DMBCore.h>
#include "spells/add_script_link_spell.h"
#include "spells/script_link_spell.h"
#include "generated/content.h"
#include "generated/types.h"
#include "spell_context.h"

#ifdef LOG_ON
LOG_PREFIX("add_script_link_spell");
LOG_POSTFIX("\n");
#endif

namespace spl
{
	const std::unordered_map<int, std::string> add_script_link_spell::s_retmessage = create_retcode_message_map();
	
	std::unordered_map<int, std::string> add_script_link_spell::create_retcode_message_map()
	{
		std::unordered_map<int, std::string> result;
		result[int(retcode::REGISTRY_ERROR)] = "Can't find spell data after its successfull creation";
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
		// Add the spell with basic data using base class method
		auto ret = base::cast(args, ctx);
		if (ret != base::retcode::OK)
			return ret;

		auto content = ctx.get_content_data();
		auto spells = content.get_spellbook().get_spells();
		auto& new_spell_alias = args.get_value("alias").value();
		auto& registry = spells.get_registry();
		auto& registry_data = registry.get_data()->AsObject();
		
		if (!registry_data.Has(new_spell_alias))
			return retcode::REGISTRY_ERROR;

		// Add path field to the created spell
		auto& new_spell_data = registry_data.Get(new_spell_alias).AsObject();
		new_spell_data.Set("path", args.get_value("path").value());

		// Add spell to script_links registry
		auto content_data = content.get_data()->AsObject();
		auto& script_links_data = (content_data.Has("script_links") ? 
			content_data.Get("script_links") : content_data.Set("script_links", vl::List())
			).AsList();
		script_links_data.Add(new_spell_alias);

		// Store DB
		if (!ctx.db().Store())
		{
			LOG_ERROR("Error occured during casting a spell '" << get_alias() << "': can't store the Spellbook");
			return base::retcode::STORE_ERROR;
		}
		return ret;
	}

}
