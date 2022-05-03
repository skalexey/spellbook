#pragma once

#include <memory>
#include <vector>
#include <string>

namespace spl
{
	class spell;
	using spell_ptr = std::shared_ptr<spell>;
	class spell_expression;
	using spell_expression_ptr = std::shared_ptr<spell_expression>;
	class context;
	class option;
	class parser;
	using option_list = std::vector<option>;
	using args_list = std::vector<std::string>;
}

