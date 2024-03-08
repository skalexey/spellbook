#include <utils/log.h>
#include <utils/file_utils.h>
#include "spell_context.h"
#include "spell_factory.h"
#include "spells/python_spell.h"
#include "spells/shell_spell.h"
#include "generated/content.h"
#ifdef LOG_ON
	LOG_TITLE("spell_factory");
	SET_LOCAL_LOG_DEBUG(true);
#endif

namespace fs = std::filesystem;

namespace spl
{
	std::unordered_map<std::string, spell_factory::creator_func_t> spell_factory::m_creator;

	bool python_spell_exists(const std::string& alias, spl::context& ctx)
	{
		auto& python_spells_path = ctx.get_content_data().get_config().python_spells_directory();
		if (utils::file::exists(python_spells_path + "/" + alias + ".py"))
			return true;
		return false;
	}

	bool shell_spell_exists(const std::string& alias, spl::context& ctx)
	{
		auto cfg = ctx.get_content_data().get_config();
		fs::path scripts_dir_path = cfg.shell_spells_directory();
		if (scripts_dir_path.is_relative())
			scripts_dir_path = fs::temp_directory_path() / scripts_dir_path;
		if (utils::file::exists(scripts_dir_path / (alias + ".sh")))
			return true;
		return false;
	}

	spell_ptr create_script_spell(const cppgen::Spell& data, spl::context& ctx)
	{
		auto& alias = data.alias();
		// Search for a python spell
		if (python_spell_exists(alias, ctx))
			return std::make_shared<python_spell>(data.get_data());
		// Search for a shell spell
		if (shell_spell_exists(alias, ctx))
			return std::make_shared<shell_spell>(data.get_data());
		return nullptr;
	}

	spell_ptr spell_factory::create(const cppgen::Spell& data, spl::context& ctx)
	{
		if (!data)
		{
			LOCAL_DEBUG("Invalid data passed to the create method");
			return nullptr;
		}
		auto& alias = data.alias();
		
		// Search for a script spell
		if (auto script_spell = spl::create_script_spell(data, ctx))
			return script_spell;
		// Search for a native spell

		auto it = m_creator.find(alias);
		if (it == m_creator.end())
		{
			LOCAL_WARNING("Can't find spell '" << alias << "' in the registry");
			return nullptr;
		}
		return it->second(data);
	}

	spell_ptr spell_factory::create_script_spell(const std::string& alias, spl::context& ctx)
	{
		cppgen::Spell data;
		data.set_alias(alias);
		return spl::create_script_spell(data, ctx);
	}

	spell_ptr spell_factory::create(const std::string& alias, spl::context& ctx)
	{
		return create(ctx.get_spell_data(alias), ctx);
	}
}
