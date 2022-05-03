#pragma once
#include "spell.h"
#include "spell_factory.h"

namespace spl
{
	class add_spell_spell : public spell
	{
	public:
		bool cast(const option_list& options) override;

	private:
		struct initializer
		{
			initializer() {
				spell_factory::register_spell<add_spell_spell>("add-spell");
			}
		};
		static const initializer m_initializer;
	};
}

