#include <filesystem>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <utils/log.h>
#include "spells/script_link_spell.h"
#include "generated/Option.h"
#include "generated/content.h"
#include "spell_context.h"

#ifdef LOG_ON
LOG_TITLE("script_link_spell")
SET_LOCAL_LOG_LEVEL(debug)
#endif

namespace fs = std::filesystem;

namespace spl
{
	int script_link_spell::cast(const option_list& args, spl::context& ctx)
	{
		LOCAL_LOG("cast link spell '" << get_alias() << "'");
		std::stringstream ss;
		auto script_path = get_data().get_data("path").as<vl::String>().Val();
		ss << script_path;
		for (auto it = args.begin(); it != args.end(); ++it)
		{
			auto&& arg = *it;
			LOCAL_DEBUG(arg.first << ": " << arg.second.value());
			ss << " " << arg.second.value();
		}
		auto cmd = ss.str();
		auto cfg = ctx.get_content_data().get_config();
		auto shell_cmd = cfg.shell_cmd();
		// Replace "$cmd" with cmd. Cmd can be any length
		std::string::size_type n = 0;
		while ((n = shell_cmd.find("$cmd", n)) != std::string::npos)
		{
			shell_cmd.replace(n, 4, cmd);
			n += cmd.size();
		}
		
		LOCAL_DEBUG("Run command '" << shell_cmd << "'");
		system(shell_cmd.c_str());
		return 0;
	}
}
