#pragma once
#include "spells/script_spell.h"
#include "spell_options.h"

namespace spl
{
	class script_link_spell : public script_spell
	{
	public:
		script_link_spell() = default;
		script_link_spell(const vl::Var& data) : script_spell(data) {};
		script_link_spell(const vl::VarPtr& data) : script_spell(data) {};
		script_link_spell(const cppgen::Spell& data) : script_spell(data) {};
		
		int cast(const option_list& args, spl::context& ctx) override;
	};
}

