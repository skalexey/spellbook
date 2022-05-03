#include "spell_context.h"
#include "spell.h"

#ifdef LOG_ON
	#include "Log.h"
	LOG_TITLE("spell")
	LOG_STREAM([]() -> std::ostream& { return std::cout; })
	SET_LOG_DEBUG(true)
#endif

namespace spl
{
	spell::spell(const vl::VarPtr& data)
		: m_data(data)
	{
	}

	bool spell::cast(const option_list& options)
	{
		if (options.empty()) // No options is a valid case
			return true;

		// Check the data
		if (!m_data)
		{
			LOG_WARNING("Attempt to cast a not initialized spell");
			return false;
		}

		auto& data = m_data->AsObject();
		if (!data)
		{
			LOG_ERROR("Data of a spell is not an object or empty");
			return false;
		}

		auto& options_data = data.Get("options").AsObject();
		if (!options_data)
		{
			LOG_ERROR("Trying to cast a spell with missing options data when there are " << options.size() << " options provided");
			return false;
		}

		for (auto& opt : options)
			if (opt.get_value().empty())
				if (auto& option_data = options_data.Get(opt.get_alias()).AsObject())
					if (option_data.Get("default_value"))
		}
		return false;
	}

	const std::string& spl::spell::get_alias() const
	{
		static std::string empty_string;
		if (!m_data)
			return empty_string;
		return m_data->AsObject().Get("alias").AsString().Val();
	}
}
