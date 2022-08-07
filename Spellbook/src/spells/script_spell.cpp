#include <utils/Log.h>
#include "spells/script_spell.h"
#ifdef LOG_ON
	LOG_TITLE("script_spell")
	SET_LOG_DEBUG(true)
#endif

namespace spl
{
	int script_spell::cast(const option_list& args, spl::context& ctx)
	{
		int erc = base::cast(args, ctx);
		if (erc != base::erc::OK)
			return erc;
		LOCAL_DEBUG("cast script spell '" << get_alias() << "\n");
		// TODO: invoke the script
		return base::erc::OK;
	}
}
