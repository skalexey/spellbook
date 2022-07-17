#include <cctype>
#include <string>
#include <vl.h>
#include <utils/Log.h>
#include "spell_options.h"
#include "generated/Option.h"
#include "generated/OrderedRegistry.h"

#ifdef LOG_ON
	LOG_TITLE("spell_options")
	SET_LOG_DEBUG(true)
#endif

namespace spl
{
	namespace options
	{
		option_list create_list(const cppgen::OrderedRegistry& options_data, const args_list& args)
		{
			option_list l;
			if (options_data)
				if (auto& registry = options_data.get_registry())
					if (auto& list = options_data.get_list())
						for (int i = 0; i < list.Size(); i++)
						{
							auto& option_alias = list.At(i).AsString().Val();
							if (auto opt_data = registry.get_data(option_alias).AsObject())
							{
								if (auto option = cppgen::Option(opt_data.Copy()))
								{
									option.set_value(i < args.size() ? args[i] : "");
									option.set_default_value(option.default_value());
									l.add(option_alias, option);
								}
								else
								{
									LOCAL_ERROR("Option '" << option_alias << "' does not have a definition or the type of the definition is not an Object");
								}
							}
						}
			return l;
		}

		option_list create_unnamed_list(const args_list& args)
		{
			option_list l;
			for (int i = 0; i < args.size(); i++)
			{
				std::string alias = "arg" + std::to_string(i);
				auto o = cppgen::Option(vl::Object());
				o.set_alias(alias);
				o.set_title(char(std::toupper(alias[0])) + alias.substr(1));
				o.set_value(args[i]);
				l.add(alias, o);
			}
			return l;
		}
	}
}


