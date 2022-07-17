#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <utils/Log.h>
#include "spells/shell_spell.h"
#include "generated/Option.h"
#include "generated/content.h"
#include "spell_context.h"

#ifdef LOG_ON
	LOG_TITLE("shell_spell")
	SET_LOG_DEBUG(true)
#endif

namespace spl
{
	int shell_spell::cast(const option_list& args, spl::context& ctx)
	{
		LOCAL_LOG("cast shell spell '" << get_alias());
		std::stringstream ss;
		auto cfg = ctx.get_content_data().get_config();
		ss << cfg.shell_cmd() << " " << cfg.shell_spells_directory() << "/" << get_alias() << ".sh";
		std::for_each(args.begin(), args.end(), [&](auto arg) {
			LOCAL_DEBUG(arg.first << ": " << arg.second.value());
			ss << " " << arg.second.value();
		});
		LOCAL_DEBUG("Run command '" << ss.str() << "'");
		system(ss.str().c_str());
		return 0;
	}
}
