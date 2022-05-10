#pragma once

#include <memory>
#include <string>
#include <vector>
#include "spell_fwd.h"

namespace spl
{
	class context;
	class spell_expression
	{
	public:
		using children_t = std::vector<spell_expression>;
		// Initializers
		spell_expression() = default;
		bool init(const std::string& alias, const args_list& args, spl::context& ctx);
		// Getters
		inline const option_list& get_args() const { return m_args; }
		inline option_list& args() { return m_args; }
		const std::string& get_alias() const;
		inline cppgen::Spell* spell_data() { return m_spell_data.get(); }
		inline const cppgen::Spell* get_spell_data() const { return m_spell_data.get(); }
		inline const children_t& get_children() const { return m_children; }
		inline children_t& children() { return m_children; }
		
		// Iterators
		// Recursively go through all subexpression including this
		bool iterate_expressions(const std::function<bool(const spell_expression&)>& pred) const;
		bool iterate_expressions(const std::function<bool(spell_expression&)>& pred);
		
		// Logic
		bool execute(spl::context& ctx);
		bool has_missed_args() const;

	private:
		std::unique_ptr<cppgen::Spell> m_spell_data;
		option_list m_args;
		children_t m_children;
	};

	using spell_expression_ptr = std::shared_ptr <spell_expression>;
}


