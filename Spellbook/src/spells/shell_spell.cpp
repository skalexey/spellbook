#include <filesystem>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <utils/log.h>
#include "spells/shell_spell.h"
#include "generated/Option.h"
#include "generated/content.h"
#include "spell_context.h"

#ifdef LOG_ON
LOG_TITLE("shell_spell")
SET_LOCAL_LOG_DEBUG(true)
#endif

namespace fs = std::filesystem;

namespace spl
{
	int shell_spell::cast(const option_list& args, spl::context& ctx)
	{
		LOCAL_LOG("cast shell spell '" << get_alias());
		std::stringstream ss;
		auto cfg = ctx.get_content_data().get_config();
		fs::path scripts_dir_path = cfg.shell_spells_directory();
		if (scripts_dir_path.is_relative())
			scripts_dir_path = fs::temp_directory_path() / scripts_dir_path;
		ss << cfg.shell_cmd() << " " << (scripts_dir_path / (get_alias() + ".sh")).string();
		std::for_each(args.begin(), args.end(), [&](auto arg) {
			LOCAL_DEBUG(arg.first << ": " << arg.second.value());
			ss << " " << arg.second.value();
		});
		LOCAL_DEBUG("Run command '" << ss.str() << "'");
		system(ss.str().c_str());
		return 0;
	}
}
