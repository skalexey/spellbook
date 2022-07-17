#include <algorithm>
#include <iostream>
#include <utils/Log.h>
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
	SET_LOG_DEBUG(false);
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
	bool spell_expression::execute(spl::context& ctx)
	{
		if (!m_spell_data)
		{
			LOCAL_DEBUG("Null data in an executing expression");
			return false;
		}
		if (auto spell = spell_factory::create(*m_spell_data, ctx))
			return spell->cast(m_args, ctx);
		LOCAL_ERROR("Can't execute the spell '" << get_alias() << "'");
		return false;
	}

	bool spell_expression::has_missed_args() const
	{
		return iterate_expressions([&](auto& ex) {
			bool result = false;
			std::for_each(ex.get_args().begin(), ex.get_args().end(), [&](auto arg) {
				if (!result)
					if (arg.second.value().empty())
						if (arg.second.default_value().empty())
							result = true;
			});
			return result;
		});
	}

	bool spell_expression::iterate_expressions(const std::function<bool(const spell_expression&)>& pred) const
	{
		ITERATE_EXPRESSIONS;
	}

	bool spell_expression::iterate_expressions(const std::function<bool(spell_expression&)>& pred)
	{
		ITERATE_EXPRESSIONS;
	}
}
