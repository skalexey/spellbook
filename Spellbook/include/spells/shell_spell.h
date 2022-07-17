#pragma once
#include "spells/script_spell.h"
#include "spell_options.h"

namespace spl
{
	class shell_spell : public script_spell
	{
	public:
		shell_spell() = default;
		shell_spell(const vl::Var& data) : script_spell(data) {};
		shell_spell(const vl::VarPtr& data) : script_spell(data) {};
		shell_spell(const cppgen::Spell& data) : script_spell(data) {};
		
		int cast(const option_list& args, spl::context& ctx) override;
	};
}

