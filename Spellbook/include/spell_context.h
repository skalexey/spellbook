#pragma once

#include <string>
#include <vector>
#include <DMBCore.h>
#include "spell_fwd.h"
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
		static void register_loader(
			const std::string& alias
			, const context_func_t& custom_loader
		) {
			m_custom_loaders[alias] = custom_loader;
		}
	private:
		dmb::Model m_spells_db;
		using custom_loaders_t = std::unordered_map<std::string, context_func_t>;
		static custom_loaders_t m_custom_loaders;
	};
}


