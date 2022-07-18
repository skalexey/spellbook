#pragma once
#include <unordered_map>
#include "add_spell_spell.h"
#include "spell_factory.h"

namespace spl
{
	class add_script_link_spell : public add_spell_spell
	{
	public:
		using base = add_spell_spell;
		enum retcode : int
		{
			REGISTRY_ERROR = base::retcode::COUNT
		};
		add_script_link_spell() = default;
		add_script_link_spell(const vl::Var& data) : base(data) {};
		add_script_link_spell(const vl::VarPtr& data) : base(data) {};
		add_script_link_spell(const cppgen::Spell& data) : base(data) {};
		
		// TODO: return struct with message and code together value from cast()
		int cast(const option_list& args, spl::context& ctx) override;
		
		static const std::string& retmessage(int code);
		
	private:
		static std::unordered_map<int, std::string> create_retcode_message_map();
		
	private:
		static const std::unordered_map<int, std::string> s_retmessage;
		using initializer = spell::initializer<add_script_link_spell>;
		static const initializer m_initializer;
	};
}

