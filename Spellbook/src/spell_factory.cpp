#include "spell_factory.h"
#ifdef LOG_ON
	#include <Log.h>
	LOG_TITLE("spell_factory")
	LOG_STREAM([]() -> std::ostream& { return std::cout; })
#endif

namespace spl
{
	std::unordered_map<std::string, spell_factory::creator_func_t> spell_factory::m_creator;

	spell_ptr spell_factory::create(const std::string& alias)
	{
		auto it = m_creator.find(alias);
		if (it == m_creator.end())
		{
			LOG_WARNING("Can't find spell '" << alias << "' in the registry");
			return nullptr;
		}
		return it->second();
	}
}