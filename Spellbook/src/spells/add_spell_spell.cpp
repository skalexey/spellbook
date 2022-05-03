#include "spells/add_spell_spell.h"

#ifdef LOG_ON
	#include "Log.h"
	LOG_TITLE("add_spell_spell")
	LOG_STREAM([]() -> std::ostream& { return std::cout; })
	SET_LOG_DEBUG(true)
#endif

namespace spl
{
	const add_spell_spell::initializer add_spell_spell::m_initializer = add_spell_spell::initializer();
	bool add_spell_spell::cast(const option_list& options)
	{
		LOG_DEBUG("CAST!");
		return true;
	}

}