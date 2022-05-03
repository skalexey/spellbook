#pragma once

#include <memory>
#include <string>
#include <vector>
#include "spell_fwd.h"

namespace spl
{
	class context;
	class spell_expression
	{
	public:
		spell_expression(const std::string& alias, const args_list& args);
		const args_list& get_args() const { return m_args; }
		const std::string& get_alias() const { return m_alias; }

	private:
		std::string m_alias;
		args_list m_args;
	};

	using spell_expression_ptr = std::shared_ptr <spell_expression>;
}


