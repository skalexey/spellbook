#pragma once

#include <memory>
#include <string>
#include <vector>
#include "spell_fwd.h"
#include "generated/fwd.h"

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
		const option_list& get_args() const { return m_args; }
		option_list& args() { return m_args; }
		const std::string& get_alias() const;
		cppgen::Spell* spell_data() { return m_spell_data.get(); }
		const cppgen::Spell* get_spell_data() const { return m_spell_data.get(); }
		const children_t& get_children() const { return m_children; }
		children_t& children() { return m_children; }
		
		// Iterators
		// Recursively go through all subexpression including this
		using expr_pred_t = std::function<bool(spell_expression&)>;
		using const_expr_pred_t = std::function<bool(const spell_expression&)>;
		bool iterate_expressions(const const_expr_pred_t& pred) const;
		bool iterate_expressions(const expr_pred_t& pred);
		using option_pred_t = std::function<bool(spell_expression&, cppgen::Option& opt)>;
		using const_option_pred_t = std::function<bool(const spell_expression&, const cppgen::Option& opt)>;
		bool iterate_options(const const_option_pred_t& pred) const;
		bool iterate_options(const option_pred_t& pred);
		
		// Logic
		int execute(spl::context& ctx);
		bool has_missed_args(spl::context& ctx) const;
		bool is_option_missed(const cppgen::Option& opt) const;
		bool is_optional(const cppgen::Option& opt) const;

	private:
		std::unique_ptr<cppgen::Spell> m_spell_data;
		option_list m_args;
		children_t m_children;
	};

	using spell_expression_ptr = std::shared_ptr <spell_expression>;
}


