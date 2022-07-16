#include <utils/Log.h>
#include "spell_context.h"
#include "spell.h"
#include "generated/Option.h"

#ifdef LOG_ON
	LOG_TITLE("spell")
	SET_LOG_DEBUG(true)
#endif

namespace spl
{
	int spell::cast(const option_list& args, spl::context& ctx)
	{
		if (!m_data)
		{
			LOG_WARNING("Attempt to cast a not initialized spell");
			return false;
		}
		return true;
	}

	const std::string& spl::spell::get_alias() const
	{
		static std::string empty_string;
		if (!m_data)
			return empty_string;
		return m_data.alias();
	}
}
