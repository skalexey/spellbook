#pragma once
#include "spells/script_spell.h"
#include "spell_options.h"

namespace spl
{
	class python_spell : public script_spell
	{
	public:
		python_spell() = default;
		python_spell(const vl::Var& data) : script_spell(data) {};
		python_spell(const vl::VarPtr& data) : script_spell(data) {};
		python_spell(const cppgen::Spell& data) : script_spell(data) {};
		
		int cast(const option_list& args, spl::context& ctx) override;
	};
}

