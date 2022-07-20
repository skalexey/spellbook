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
		// Creates a list of options with only values set and all other fields are invalid.
		option_list create_unnamed_list(const args_list& args);
	}
}


