#include <utils/Log.h>
#include <utils/file_utils.h>
#include "spell_context.h"
#include "spell_factory.h"
#include "spells/python_spell.h"
#include "generated/content.h"
#ifdef LOG_ON
	LOG_TITLE("spell_factory");
	LOG_STREAM([]() -> std::ostream& { return std::cout; });
	SET_LOG_DEBUG(true);
#endif

namespace spl
{
	std::unordered_map<std::string, spell_factory::creator_func_t> spell_factory::m_creator;

	bool python_spell_exists(const std::string& alias, spl::context& ctx)
	{
		auto& python_spells_path = ctx.get_content_data().get_config().python_spells_directory();
		if (utils::file_exists(python_spells_path + "/" + alias + ".py"))
			return true;
		return false;
	}

	spell_ptr create_python_spell(const cppgen::Spell& data, spl::context& ctx)
	{
		return std::make_shared<python_spell>(data.get_data());
		LOCAL_ERROR("Can't find data for the python spell '" << data.alias() << "'");
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
		// Search for a python spell
		if (python_spell_exists(alias, ctx))
			return create_python_spell(data, ctx);
		
		// Search for a native spell
		auto it = m_creator.find(alias);
		if (it == m_creator.end())
		{
			LOCAL_WARNING("Can't find spell '" << alias << "' in the registry");
			return nullptr;
		}
		return it->second(data);
	}

	spell_ptr spell_factory::create(const std::string& alias, spl::context& ctx)
	{
		return create(ctx.get_spell_data(alias), ctx);
	}
}
