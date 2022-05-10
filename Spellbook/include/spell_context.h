#pragma once

#include <string>
#include <vector>
#include <DMBCore.h>
#include "generated/fwd.h"

namespace spl
{
	class context
	{
	public:
		context();
		bool load_spells(const std::string& file_path);
		cppgen::Spell get_spell_data(const std::string& alias) const;
		cppgen::content get_content_data() const;
		cppgen::types get_types_data() const;
		inline dmb::Model& db() {
			return m_spells_db;
		}
		inline const dmb::Model& db() const {
			return m_spells_db;
		}
	private:
		dmb::Model m_spells_db;
	};
}


