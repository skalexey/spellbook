#include "generated/Option.h"
#include "generated/Spell.h"
#include "spell_expression.h"
#include "spell_parser.h"
#include "spell_context.h"
#include "utils/string_utils.h"
#include <utils/Log.h>
#ifdef LOG_ON
	LOG_TITLE("parser")
#endif

namespace spl
{
	struct parse_context
	{
		std::string left_to_parse;
		spl::context& external_ctx;
		char const** argv = nullptr;
		int argc = 0;
		spell_expression_ptr root_expr = nullptr;
		spell_expression_ptr current_expr = nullptr;
	};
	
	bool remove_leading(std::string& s, char ch)
	{
		if (s.empty())
			return false;
		if (s[0] == ch)
		{
			auto p = s.find_first_not_of(ch);
			if (p != std::string::npos)
			{
				s.erase(s.begin(), s.begin() + p);
				if (s.empty())
					return false;
			}
			else
			{
				s.clear();
				return false;
			}
		}
		return true;
	}

	//std::string next_token(std::string& s)
	//{
	//	if (!remove_leading(s, ' '))
	//		return "";
	//	
	//	auto pos = s.find_first_of(' ');
	//	auto t = s.substr(0, pos);
	//	if (pos != std::string::npos)
	//	{
	//		auto pos2 = s.find_first_not_of(' ', pos);
	//		// TODO: check for when nothing but the spaces is left
	//		if (pos2 == std::string::npos)
	//			s.clear();
	//		else
	//			s = s.substr(pos2);
	//	}
	//	else
	//		s.clear();
	//	return t;
	//}

	std::string next_token(std::string& s)
	{
		return std::move(s);
	}
	//std::string find_end (std::string& s, char findee)
	//{
	//	auto pos = s.find_first_of(findee);
	//	auto t = s.substr(0, pos);
	//	if (pos != std::string::npos)
	//	{
	//		if (s[pos] == '"')
	//		{
	//			auto pos2 = s.find_first_not_of(' ', pos);
	//		}
	//		else
	//		{
	//			auto pos2 = s.find_first_not_of(' ', pos);
	//		}
	//		// TODO: check for when nothing but the spaces is left
	//		s = s.substr(pos2);
	//	}
	//	else
	//	{
	//		if (findee == '"')
	//			return find_end(' ');
	//		s.clear();
	//	}
	//};

	//std::string next_literal(std::string& s)
	//{
	//	if (s.empty())
	//		return "";
	//	char findee = s[0] == '"' ? '"' : ' ';
	//	
	//	if (!remove_leading(s, findee))
	//		return "";
	//	find_end(findee);
	//	
	//	return t;
	//}

	//bool parse_impl(parse_context& ctx)
	//{
	//	auto& s = ctx.left_to_parse;
	//	auto& ex = ctx.current_expr;
	//	auto token = next_token(s);
	//	if (token.empty() && !ex)
	//		return false;

	//	// Temporarily the simplest parser
	//	auto& spell_alias = token;
	//	if (auto data = ctx.external_ctx.get_spell_data(spell_alias))
	//	{
	//		auto ex = std::make_shared<spell_expression>();
	//		//args_list args;
	//		//while (true)
	//		//{
	//		//	auto l = next_literal(s);
	//		//	if (!l.empty())
	//		//		args.push_back(l);
	//		//	else
	//		//		break;
	//		//}
	//		//ex->init(spell_alias, args, ctx.external_ctx);
	//		ex->init(spell_alias, args_list(), ctx.external_ctx);
	//		ctx.root_expr = ex;
	//	}
	//	else
	//	{
	//		LOCAL_ERROR("Can't find spell data '" << spell_alias << "'");
	//	}
	//	return true;
	//}

	bool parse_impl(parse_context& ctx)
	{
		// Temporarily the simplest parser
		if (ctx.argv && ctx.argc < 2)
			return false;
		auto spell_alias = ctx.argv ? ctx.argv[1] : next_token(ctx.left_to_parse);
		if (spell_alias.empty() && !ctx.current_expr)
			return false;
		auto ex = std::make_shared<spell_expression>();
		auto args = ctx.argv && ctx.argc > 2 ? args_list(&ctx.argv[2], ctx.argv + ctx.argc) : args_list();
		ex->init(spell_alias, args, ctx.external_ctx);
		ctx.root_expr = ex;
		return true;
	}

    spell_expression_ptr parser::parse(const std::string& s, spl::context& ctx)
    {
		parse_context parse_ctx = {s, ctx};
		parse_impl(parse_ctx);
		return parse_ctx.root_expr;
    }

	spell_expression_ptr parser::parse(int argc, char const** argv, spl::context& ctx)
	{
		parse_context parse_ctx = { "", ctx, argv, argc};
		parse_impl(parse_ctx);
		return parse_ctx.root_expr;
	}
}
