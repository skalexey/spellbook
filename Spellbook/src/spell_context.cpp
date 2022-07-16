#include <iostream>
#include "spell_context.h"
#include "generated/Option.h"
#include "generated/Spell.h"
#include "generated/content.h"
#include "generated/types.h"
#include <utils/Log.h>
#ifdef LOG_ON
	#include <vl.h>
	#include <DMBCore.h>
	LOG_TITLE("spell_context")
#endif

namespace spl
{
	context::context()
	{
	}

	cppgen::Spell context::get_spell_data(const std::string& alias) const
	{
		if (!m_spells_db.IsLoaded())
			return cppgen::Spell();
		auto data = cppgen::content(m_spells_db.GetContent().GetData());
		auto& sb = data.get_spellbook();
		if (!sb)
		{
			LOCAL_ERROR("Ops. You have no 'spellbook' field in the configuration file");
			return cppgen::Spell();
		}
		auto& spells = sb.get_spells();
		auto& registry = spells.get_registry();
		return cppgen::Spell(registry.get_data(alias));
	}
	
	cppgen::content context::get_content_data() const
	{
		if (!m_spells_db.IsLoaded())
			return cppgen::content();
		return cppgen::content(m_spells_db.GetContent().GetData());
	}

	cppgen::types context::get_types_data() const
	{
		if (!m_spells_db.IsLoaded())
			return cppgen::types();
		return cppgen::types(m_spells_db.GetRegistry().GetData());
	}

	bool context::load_spells(const std::string& file_path)
	{
		LOCAL_LOG("load_spells()");
		vl::Object db;
		bool result = m_spells_db.Load(file_path);
		if (result)
			LOCAL_LOG("Loaded");
		else
			LOCAL_LOG("Can't load spells from '" << file_path << "'");
		return result;
	}
}
