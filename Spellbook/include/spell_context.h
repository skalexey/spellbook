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
		friend class spell;
		friend class spell_expression;

	public:
		context();
		bool load_spells(const std::string& file_path);
		cppgen::Spell get_spell_data(const std::string& alias) const;
		cppgen::content get_content_data() const;
		cppgen::types get_types_data() const;
		inline dmb::Model& db() {
			if (m_store_allowed)
				return m_spells_db;
			else
			{
				static dmb::Model empty_model;
				return empty_model;
			}
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
		// Returns a flag for determine wether to ask optional parameters or not
		inline bool ask_optional() const {
			return m_ask_optional;
		}
		inline void set_ask_optional(bool value) {
			m_ask_optional = value;
		}
		inline void set_store_allowed(bool value) {
			m_store_allowed = value;
		}
		inline const bool store_allowed() const {
			return m_store_allowed;
		}
		inline const std::string last_spell_msg() const {
			return m_last_spell_msg;
		}

	protected:
		inline void set_last_spell_msg(const std::string& s) {
			m_last_spell_msg = s;
		}
	private:
		dmb::Model m_spells_db;
		using custom_loaders_t = std::unordered_map<std::string, context_func_t>;
		bool m_ask_optional = false;
		bool m_store_allowed = true;
		std::string m_last_spell_msg;

	private:
		// Static data
		static custom_loaders_t m_custom_loaders;
	};
}


