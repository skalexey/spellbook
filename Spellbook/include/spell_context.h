#pragma once

#include <string>
#include <vector>
#include <DMBCore.h>

namespace spl
{
	class context
	{
	public:
		context();
		bool load_spells(const std::string& file_path);
		vl::Object get_spell_data(const std::string& alias);

	private:
		dmb::Model m_spells_db;
	};
}


