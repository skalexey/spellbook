#pragma once
#include "spell.h"
#include "spell_options.h"

namespace spl
{
	class python_spell : public spell
	{
	public:
		python_spell() = default;
		python_spell(const vl::Var& data) : spell(data) {};
		python_spell(const vl::VarPtr& data) : spell(data) {};
		python_spell(const cppgen::Spell& data) : spell(data) {};
		
		int cast(const option_list& args, spl::context& ctx) override;
	};
}

