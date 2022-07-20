// Atomic spell interface.
// You can implement your own native spell using this class doing the following steps:
// 	* Implement cast() method.
//	* Register your spell using initializer
//		- Declare initializer:
//			static spell::initializer<your_class> m_initializer;
//		- Initialize it:
//			spell::initializer<your_class> your_class::m_initializer("your-spell-alias")
//		Your class will be registered in the system at static construction time

#pragma once
#include <string>
#include <vl_fwd.h>
#include "generated/Spell.h"
#include "spell_options.h"
#include "spell_factory.h"
#include "spell_fwd.h"
#include "spell_context.h"

namespace spl
{
	class spell
	{
	public:
		spell() = default;
		spell(const vl::Var& data) : m_data(data) {};
		spell(const vl::VarPtr& data) : m_data(data) {};
		spell(const cppgen::Spell& data) : m_data(data) {};
		virtual int cast(const option_list& args, spl::context& ctx);
		const std::string& get_alias() const;

	protected:
		template <typename T>
		struct initializer
		{
			inline initializer(
				const std::string& alias
				, const context_func_t& custom_loader = nullptr) {
				spell_factory::register_spell<T>(alias);
				if (custom_loader)
					spl::context::register_loader(alias, custom_loader);
			}
		};

	protected:
		inline const cppgen::Spell& get_data() const {
			return m_data;
		}

		inline void set_last_spell_msg(context& ctx, const std::string& msg) {
			ctx.set_last_spell_msg(msg);
		}

	private:
		cppgen::Spell m_data;
	};
}

