#include <algorithm>
#include <iostream>
#include <utils/log.h>
#include "generated/Spell.h"
#include "generated/Option.h"
#include "spell_options.h"
#include "spell_expression.h"
#include "spell_context.h"
#include "spell_parser.h"
#include "spell_factory.h"
#include "spell.h"

#ifdef LOG_ON
	LOG_TITLE("spell_expression")
	SET_LOCAL_LOG_DEBUG(false);
#endif

namespace
{
	const std::string empty_string;
}

#define ITERATE_EXPRESSIONS \
	if (!pred(*this)) \
		return false; \
	for (auto& c : m_children) \
		if (!pred(c)) \
			return false; \
	return true

namespace spl
{
	// Initializers
	bool spell_expression::init(const std::string& alias, const args_list& args, context& ctx)
	{
		if (!alias.empty())
			if (auto data = ctx.get_spell_data(alias))
				m_spell_data = std::make_unique<cppgen::Spell>(data);
		if (m_spell_data)
			m_args = options::create_list(m_spell_data->get_options(), args);
		else
		{
			m_spell_data = std::make_unique<cppgen::Spell>(vl::Object());
			m_spell_data->set_alias(alias);
			m_args = options::create_unnamed_list(args);
		}
		return true;
	}

	// Getters
	const std::string& spell_expression::get_alias() const
	{
		return m_spell_data ? m_spell_data->alias() : empty_string;
	}

	// Logic
	int spell_expression::execute(spl::context& ctx)
	{
		if (!m_spell_data)
		{
			LOCAL_DEBUG("Null data in an executing expression");
			return -1;
		}
		if (auto spell = spell_factory::create(*m_spell_data, ctx))
			return spell->cast(m_args, ctx);
		ctx.set_last_spell_msg("Can't execute the spell '" + get_alias() + "'");
		return -1;
	}

	bool spell_expression::is_optional(const cppgen::Option& opt) const
	{
		return opt.has_data_own("default_value");
	}

	bool spell_expression::is_option_missed(const cppgen::Option& opt) const
	{
		auto& args = get_args();
		if (!is_optional(opt))
		{
			auto& alias = opt.alias();
			auto it = args.find(alias);
			if (it == args.end() || (*it).second.value().empty())
				return true;
		}
		return false;
	}

	bool spell_expression::has_missed_args(spl::context& ctx) const
	{
		return !iterate_options([&](auto& ex, auto& opt) -> bool {
			auto& args = ex.get_args();
			if (ex.is_option_missed(opt) || ctx.ask_optional())
				return false; // The argument has not been given, so stop the process
			return true;
		});
	}

	bool spell_expression::iterate_expressions(const const_expr_pred_t& pred) const
	{
		ITERATE_EXPRESSIONS;
	}

	bool spell_expression::iterate_expressions(const expr_pred_t& pred)
	{
		ITERATE_EXPRESSIONS;
	}

	template <typename TPred, typename TExpr>
	bool iterate_options_impl(const TPred& pred, TExpr&& ex)
	{
		return ex.iterate_expressions([&](auto& ex) -> bool {
			if (auto spell_data = ex.get_spell_data())
				if (auto& options = spell_data->get_options())
				{
					auto& list = options.get_list();
					for (int i = 0; i < list.Size(); i++)
					{
						auto& alias = list.At(i).AsString().Val();
						if (auto& opt_data = options.get_registry().get_data()->AsObject().Get(alias))
						{
							auto opt = cppgen::Option(opt_data);
							if (!pred(ex, opt))
								return false;
						}
					}
				}
			return true;
		});
	}

	bool spell_expression::iterate_options(const const_option_pred_t& pred) const
	{
		return iterate_options_impl(pred, *this);
	}

	bool spell_expression::iterate_options(const option_pred_t& pred)
	{
		return iterate_options_impl(pred, *this);
	}
}
