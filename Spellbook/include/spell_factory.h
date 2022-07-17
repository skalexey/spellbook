#pragma once

#include <functional>
#include <unordered_map>
#include <string>
#include <vl_fwd.h>
#include "generated/Spell.h"
#include "spell_fwd.h"

namespace spl
{
	class spell_factory
	{
	public:
		using creator_func_t = std::function<spell_ptr(const cppgen::Spell& data)>;
		static spell_ptr create(const std::string& alias, spl::context& ctx);
		static spell_ptr create(const cppgen::Spell& data, spl::context& ctx);
		template <typename T>
		static void register_spell(const std::string& alias) {
			m_creator[alias] = [] (const cppgen::Spell& data){
				return std::make_shared<T>(data);
			};
		}
		static spell_ptr create_script_spell(const std::string& alias, spl::context& ctx);

	private:
		static std::unordered_map<std::string, creator_func_t> m_creator;
	};
}


