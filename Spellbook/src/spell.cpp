#include <utils/log.h>
#include "spell_context.h"
#include "spell.h"
#include "generated/Option.h"

#ifdef LOG_ON
	LOG_TITLE("spell")
	SET_LOCAL_LOG_DEBUG(true)
#endif

namespace spl
{
	int spell::cast(const option_list& args, spl::context& ctx)
	{
		ctx.set_last_spell_msg("");
		if (!m_data)
		{
			ctx.set_last_spell_msg("Attempt to cast a not initialized spell");
			return erc::NO_DATA;
		}
		return erc::OK;
	}

	const std::string& spl::spell::get_alias() const
	{
		static std::string empty_string;
		if (!m_data)
			return empty_string;
		return m_data.alias();
	}
}
