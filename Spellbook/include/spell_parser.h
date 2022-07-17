#pragma once

#include <string>
#include "spell_fwd.h"

namespace spl
{
	class parser
	{
	public:
		static spell_expression_ptr parse(const std::string& s, spl::context& ctx);
		static spell_expression_ptr parse(int argc, char const** argv, spl::context& ctx);
	};
}

