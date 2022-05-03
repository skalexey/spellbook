#include <iostream>
#include "spell_context.h"
#ifdef LOG_ON
	#include <Log.h>
	#include <vl.h>
	#include <DMBCore.h>
	LOG_TITLE("spell_context")
	LOG_STREAM([]() -> std::ostream& { return std::cout; })
#endif

namespace spl
{
	context::context()
	{
	}

	vl::Object context::get_spell_data(const std::string& alias)
	{
		if (!m_spells_db.IsLoaded())
			return vl::nullObject;
		auto& data = m_spells_db.GetContent().GetData();
		auto& sb = data.Get("spellbook").AsObject();
		if (!sb)
			return vl::nullObject;
		auto& spells = sb.Get("spells").AsObject();
		auto& registry = spells.Get("registry").AsObject();
		auto& spell = registry.Get(alias).AsObject();
		return spell;
	}
	
	bool context::load_spells(const std::string& file_path)
	{
		LOCAL_LOG("load_spells()\n");
		vl::Object db;
		bool result = m_spells_db.Load(file_path);
		if (result)
			LOCAL_LOG("Loaded\n");
		else
			LOCAL_LOG("Can't load spells from '" << file_path << "'\n");
		return result;
	}
}