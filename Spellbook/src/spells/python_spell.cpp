#include "spells/python_spell.h"
#ifdef LOG_ON
	#include "Log.h"
	LOG_TITLE("python_spell")
	LOG_STREAM([]() -> std::ostream& { return std::cout; })
	SET_LOG_DEBUG(true)
#endif

namespace spl
{
	bool python_spell::cast(const option_list& options)
	{
		LOCAL_DEBUG("cast python spell '" << get_alias() << "\n");
		return true;
	}
}