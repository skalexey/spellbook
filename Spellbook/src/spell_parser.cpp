#include "generated/Option.h"
#include "generated/Spell.h"
#include "spell_expression.h"
#include "spell_parser.h"
#include "spell_context.h"
#include "utils/string_utils.h"
#include <utils/Log.h>
#ifdef LOG_ON
	LOG_TITLE("parser")
	LOG_STREAM([]() -> std::ostream& { return std::cout; })
#endif

namespace spl
{
	struct parse_context
	{
		std::string left_to_parse;
		spl::context& external_ctx;
		spell_expression_ptr root_expr = nullptr;
		spell_expression_ptr current_expr = nullptr;
	};
	
	std::string next_token(std::string& s)
	{
		return std::move(s);
	}

	bool parse_impl(parse_context& ctx)
	{
		auto& s = ctx.left_to_parse;
		auto& ex = ctx.current_expr;
		auto token = next_token(s);
		if (token.empty() && !ex)
			return false;

		// Temporarily the simplest parser
		auto& spell_alias = token;
		if (auto data = ctx.external_ctx.get_spell_data(spell_alias))
		{
			auto ex = std::make_shared<spell_expression>();
			ex->init(spell_alias, args_list(), ctx.external_ctx);
			ctx.root_expr = ex;
		}
		else
		{
			LOCAL_ERROR("Can't find spell data '" << spell_alias << "'");
		}
		return true;
	}

    spell_expression_ptr parser::parse(const std::string& s, spl::context& ctx)
    {
		parse_context parse_ctx = {s, ctx};
		parse_impl(parse_ctx);
		return parse_ctx.root_expr;
    }
}
