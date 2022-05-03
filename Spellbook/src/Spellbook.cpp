// Spellbook.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <string>
#include <vl_fwd.h>
#include "Log.h"
#include "Spellbook.h"	
#include "spell_parser.h"
#include "spell_expression.h"
#include "spell_context.h"
#include "spell_factory.h"
#include "spell_options.h"
#include "spell.h"

#ifdef LOG_ON
	#include "Log.h"
	LOG_TITLE("Spellbook")
	LOG_STREAM([]() -> std::ostream& { return std::cout; })
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

namespace spl
{
	bool cast_spell(const spell_expression& ex, context& ctx)
	{
		LOCAL_DEBUG("Cast()\n");
		if (const auto& data = ctx.get_spell_data(ex.get_alias()))
		{
			auto& rules = data.Get("rules").AsString().Val();
			if (!rules.empty())
			{
				if (auto spell_ex = parser::parse(rules))
					return cast_spell(*spell_ex, ctx);
			}
			else
			{
				if (auto spell = spell_factory::create(data.Get("alias").AsString().Val()))
					return spell->cast(options::create_list(data.Get("options"), ex.get_args()), ctx);
			}
		}
		else
			LOCAL_LOG("Can't figure out what you've said");
		return false;
	}
}

int main()
{
	LOG("=== Spellbook Project ===\n");
	spl::context ctx;
	if (!ctx.load_spells("spellbook.json"))
	{
		std::cout << "Seems like you have no spells...\n";
		return false;
	}
	std::string s;
	while (true)
	{
		std::cout << "Your spell: ";
		std::getline(std::cin, s);
		if (s == "exit")
			break;
		std::cout << "\n";
		if (auto spellEx = spl::parser::parse(s))
			spl::cast_spell(*spellEx, ctx);
		else
			std::cout << "	Can't figure out what you've said\n";
	}
	return 0;
}
