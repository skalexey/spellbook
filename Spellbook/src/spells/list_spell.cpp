#include <iostream>
#include <unordered_map>
#include <vl.h>
#include <utils/Log.h>
#include "spells/list_spell.h"
#include "generated/content.h"
#include "generated/types.h"
#include "spell_context.h"

LOG_PREFIX("[list_spell]: ");
LOG_POSTFIX("\n");

#define MSG(m) std::cout << m << '\n'

namespace spl
{
	// Static spell registrator
	const list_spell::initializer list_spell::m_initializer("list");
	int list_spell::cast(const option_list& args, spl::context& ctx)
	{
		auto spells = ctx.get_content_data().get_spellbook().get_spells();
		auto& list = spells.get_list();
		for (int i = 0; i < list.Size(); i++)
			MSG(list.At(i).AsString().Val());
		return retcode::OK;
	}

}
