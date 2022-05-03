#pragma once
#include "spell.h"
#include "spell_options.h"

namespace spl
{
	class python_spell : public spell
	{
	public:
		bool cast(const option_list& options) override;
	};
}

