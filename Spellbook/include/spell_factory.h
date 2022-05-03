#pragma once

#include <functional>
#include <unordered_map>
#include <string>
#include "spell_fwd.h"

namespace spl
{
	class spell_factory
	{
	public:
		using creator_func_t = std::function<spell_ptr()>;
		static spell_ptr create(const std::string& alias);
		template <typename T>
		static void register_spell(const std::string& alias) {
			m_creator[alias] = [] {
				return std::make_shared<T>();
			};
		}
	private:
		static std::unordered_map<std::string, creator_func_t> m_creator;
	};
}


