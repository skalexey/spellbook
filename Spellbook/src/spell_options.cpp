#include <cctype>
#include <string>
#include <vl.h>
#include <utils/log.h>
#include "spell_options.h"
#include "generated/Option.h"
#include "generated/OrderedRegistry.h"

#ifdef LOG_ON
	LOG_TITLE("spell_options")
	SET_LOCAL_LOG_DEBUG(true)
#endif

namespace
{
	cppgen::Option create_unnamed_option(const std::string& val, int arg_index)
	{
		std::string alias = "arg" + std::to_string(arg_index);
		auto o = cppgen::Option(vl::Object());
		o.set_alias(alias);
		o.set_title(char(std::toupper(alias[0])) + alias.substr(1));
		o.set_value(val);
		return o;
	}
}

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
						for (int i = 0; i < args.size(); i++)
						{
							if (list.Size() > i)
							{
								auto& option_alias = list.At(i).AsString().Val();
								if (auto opt_data = registry.get_data(option_alias).AsObject())
								{
									if (auto option = cppgen::Option(opt_data.Copy()))
									{
										if (args.size() > i)
										{
											option.set_value(args[i]);
											l.add(option_alias, option);
										}
									}
									else
									{
										LOCAL_ERROR("Option '" << option_alias << "' does not have a definition or the type of the definition is not an Object");
									}
								}
							}
							else
							{
								auto o = create_unnamed_option(args[i], i);
								l.add(o.alias(), o);
							}
						}
			return l;
		}

		option_list create_unnamed_list(const args_list& args)
		{
			option_list l;
			for (int i = 0; i < args.size(); i++)
			{
				auto o = create_unnamed_option(args[i], i);
				l.add(o.alias(), o);
			}
			return l;
		}
	}
}


