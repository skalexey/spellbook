// Spellbook.cpp : Defines the entry point for the application.
//

#include <filesystem>
#include <algorithm>
#include <iostream>
#include <string>
#include <vl_fwd.h>
#include <utils/Log.h>
#include "generated/Spell.h"
#include "generated/Option.h"
#include "Spellbook.h"	
#include "spell_parser.h"
#include "spell_expression.h"
#include "spell_context.h"
#include "spell_factory.h"
#include "spell_options.h"
#include "spell.h"
#ifdef LOG_ON
	LOG_TITLE("Spellbook")
	SET_LOG_DEBUG(true)
#endif

// Participants
//	* parser
//		* parse(string)
//	* spell_expression
//		* cast() / run / invoke / call
//		* alias
//		* options
//	* context
//		* spell_list
//

bool request_argument(cppgen::Option& opt)
{
	std::cout << "\t" << opt.title() << ": ";
	std::string val;
	std::cin >> val;
	opt.set_value(val);
	// TODO: check the option validity
	return true;
}

bool request_missed_args(spl::spell_expression& ex, spl::context& ctx)
{
	return ex.iterate_expressions([&](spl::spell_expression& ex) {
		bool result = true;
		std::for_each(ex.get_args().begin(), ex.get_args().end(), [&](auto arg) {
			if (result)
				if (arg.second.value().empty())
					if (arg.second.default_value().empty())
						if (!request_argument(arg.second))
							result = false; // The argument has not been given, so stop the process
		});
		return result;
	});
}

int main(int argc, char const* argv[])
{
	LOG("=== Spellbook Project ===\n");
	spl::context ctx;
	if (!ctx.load_spells("spellbook.json"))
	{
		std::cout << "Seems like you have no spells...\n";
		return -1;
	}

	auto process_ex_args = [&](const spl::spell_expression_ptr& ex) {
		if (ex->has_missed_args())
			if (!request_missed_args(*ex, ctx))
			{
				std::cout << "	Some arguments has been not provided. Can't cast the spell\n";
				return false;
			}
		return true;
	};

	auto on_cant_parse = [] {
		std::cout << "	Can't figure out what you've said\n";
	};

	if (argc < 2)
	{
		std::string s;
		while (true)
		{
			std::cout << "Your spell: ";
			std::getline(std::cin, s);
			if (s == "exit")
				break;
			std::cout << "\n";
			//		std::cout << " parse string '" << s << "'\n";
			if (s.empty())
				continue;
			if (auto spell_ex = spl::parser::parse(s, ctx))
			{
				if (!process_ex_args(spell_ex))
					continue;
				int result = spell_ex->execute(ctx);
			}
			else
				on_cant_parse();
			s.clear();
		}
	}
	else
	{
		if (auto spell_ex = spl::parser::parse(argc, argv, ctx))
		{
			if (process_ex_args(spell_ex))
				int result = spell_ex->execute(ctx);
		}
		else
			on_cant_parse();
	}
	return 0;
}
