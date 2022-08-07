#pragma once
#include <unordered_map>
#include "spell.h"
#include "spell_factory.h"

namespace spl
{
	class add_spell_spell : public spell
	{
		using base = spell;
	public:
		add_spell_spell() = default;
		add_spell_spell(const vl::Var& data) : spell(data) {};
		add_spell_spell(const vl::VarPtr& data) : spell(data) {};
		add_spell_spell(const cppgen::Spell& data) : spell(data) {};
		
		enum erc : int
		{
			ALREADY_EXISTS = base::erc::COUNT,
			DATA_ERROR,
			OPTION_MISSED,
			STORE_ERROR,
			COUNT
		};
		// TODO: return struct with message and code together value from cast()
		int cast(const option_list& args, spl::context& ctx) override;
		
		static const std::string& retmessage(int code);
		
	private:
		static std::unordered_map<int, std::string> create_retcode_message_map();
		
	private:
		static const std::unordered_map<int, std::string> s_retmessage;
		using initializer = spell::initializer<add_spell_spell>;
		static const initializer m_initializer;
	};
}

