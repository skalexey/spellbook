#include <vl.h>
#include "spell_options.h"

#ifdef LOG_ON
	#include "Log.h"
	LOG_TITLE("spell_options")
	LOG_STREAM([]() -> std::ostream& { return std::cout; })
	SET_LOG_DEBUG(true)
#endif

namespace spl
{
	option::option(vl::Var& data)
		: m_data(vl::MakePtr(data))
	{
	}

	const std::string& option::get_alias() const
	{
		static std::string empty_string;
		if (!m_data)
		{
			LOCAL_WARNING("get_alias() called on an unitialized option");
			return empty_string;
		}
		if (auto& data = m_data->AsObject())
			return m_data->AsObject().Get("alias").AsString().Val();
		else
		{
			LOCAL_ERROR("get_alias() called on an option with data existed but of a wrong type or is empty");
			return empty_string;
		}
	}

	const std::string& option::get_alias() const
	{
		static std::string empty_string;
		if (!m_data)
		{
			LOCAL_WARNING("get_alias() called on an unitialized option");
			return empty_string;
		}
		if (auto& data = m_data->AsObject())
			return m_data->AsObject().Get("alias").AsString().Val();
		else
		{
			LOCAL_ERROR("get_alias() called on an option with data existed but of a wrong type or is empty");
			return empty_string;
		}
	}

	

	namespace options
	{
		option_list create_list(const vl::Var& options_data, const args_list& args)
		{
			option_list l;
			if (auto o = options_data.AsObject())
				if (auto& registry = o.Get("registry").AsObject())
					if (auto& list = o.Get("list").AsList())
						for (int i = 0; i < list.Size(); i++)
						{
							auto& option_alias = list.At(i).AsString().Val();
							if (auto& option = registry.Get(option_alias).AsObject())
							{
								l.emplace_back(
									option_alias
									, i < args.size() ? args[i] : ""
									, option.Get("default_value").AsString().Val()
								);
							}
							else
							{
								LOCAL_ERROR("Option '" << option_alias << "' does not have a definition or the type of the definition is not Object");
							}
						}
			return l;
		}
	}
}


