#include <utils/log.h>
#include "spells/python_spell.h"
#ifdef LOG_ON
	LOG_TITLE("python_spell")
	SET_LOCAL_LOG_DEBUG(true)
#endif

namespace spl
{
	int python_spell::cast(const option_list& args, spl::context& ctx)
	{
		LOCAL_DEBUG("cast python spell '" << get_alias() << "\n");
		// TODO: invoke the script
		return 0;
	}
}
