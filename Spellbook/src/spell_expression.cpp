#include <iostream>
#include "spell_expression.h"
#include "spell_context.h"
#include "spell_parser.h"
#ifdef LOG_ON
	#include "Log.h"
	LOG_TITLE("spell_expression")
	LOG_STREAM([]() -> std::ostream& { return std::cout; })
	SET_LOG_DEBUG(false);
#endif

namespace spl
{
	spell_expression::spell_expression(const std::string& alias, const args_list& args)
		: m_alias(alias)
		, m_args(args)
	{
	}
}