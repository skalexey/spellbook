#include <filesystem>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <utils/Log.h>
#include "spells/script_link_spell.h"
#include "generated/Option.h"
#include "generated/content.h"
#include "spell_context.h"

#ifdef LOG_ON
LOG_TITLE("script_link_spell")
SET_LOG_DEBUG(true)
#endif

namespace fs = std::filesystem;

namespace spl
{
	int script_link_spell::cast(const option_list& args, spl::context& ctx)
	{
		LOCAL_LOG("cast link spell '" << get_alias() << "'");
		std::stringstream ss;
		auto script_path = get_data().get_data("path").AsString().Val();

		auto cfg = ctx.get_content_data().get_config();
		ss << cfg.shell_cmd() << " " << script_path;
		std::for_each(args.begin(), args.end(), [&](auto arg) {
			LOCAL_DEBUG(arg.first << ": " << arg.second.value());
			ss << " " << arg.second.value();
		});
		LOCAL_DEBUG("Run command '" << ss.str() << "'");
		system(ss.str().c_str());
		return 0;
	}
}
