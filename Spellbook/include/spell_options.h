#pragma once

#include <string>
#include <vector>
#include <vl_fwd.h>
#include "spell_fwd.h"
#include "generated/fwd.h"

namespace spl
{
	namespace options
	{
		option_list create_list(const cppgen::OrderedRegistry& options_data, const args_list& args);
	}
}


