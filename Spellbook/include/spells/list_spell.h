#pragma once
#include <unordered_map>
#include "spell.h"
#include "spell_factory.h"

namespace spl
{
	class list_spell : public spell
	{
		using base = spell;

	public:
		list_spell() = default;
		list_spell(const vl::Var& data) : spell(data) {};
		list_spell(const vl::VarPtr& data) : spell(data) {};
		list_spell(const cppgen::Spell& data) : spell(data) {};

		// TODO: return struct with message and code together value from cast()
		int cast(const option_list& args, spl::context& ctx) override;

	private:
		using initializer = spell::initializer<list_spell>;
		static const initializer m_initializer;
	};
}

