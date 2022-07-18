#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <string>
#include <utils/ordered_map.h>
#include "generated/fwd.h"

namespace spl
{
	class spell;
	using spell_ptr = std::shared_ptr<spell>;
	class spell_expression;
	using spell_expression_ptr = std::shared_ptr<spell_expression>;
	class context;
	class parser;
	using option_list = utils::ordered_map<std::string, cppgen::Option>;
	using args_list = std::vector<std::string>;
	using context_func_t = std::function<void(spl::context&)>;
}

