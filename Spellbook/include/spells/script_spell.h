#pragma once
#include "spell.h"
#include "spell_options.h"

namespace spl
{
	class script_spell : public spell
	{
		using base = spell;

	public:
		script_spell() = default;
		script_spell(const vl::Var& data) : spell(data) {};
		script_spell(const vl::VarPtr& data) : spell(data) {};
		script_spell(const cppgen::Spell& data) : spell(data) {};
		
		int cast(const option_list& args, spl::context& ctx) override;
	};
}

