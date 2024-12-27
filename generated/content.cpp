#include <vl.h>
#include "content.h"

namespace cppgen
{
	// Initializers
	
	content::content(const vl::VarPtr& data)
		: m_data(data)
	{
		if (!m_data)
			return;
		if (!m_data->is<vl::Object>())
			return;
		auto& data_obj = m_data->as<vl::Object>();
		m_spellbook = {data_obj.GetDef("spellbook")};
		m_config = {data_obj.GetDef("config")};
	}
	
	content::content(const vl::Var& data)
		: m_data(vl::MakePtr(data))
	{
		if (!m_data)
			return;
		if (!m_data->is<vl::Object>())
			return;
		auto& data_obj = m_data->as<vl::Object>();
		m_spellbook = {data_obj.GetDef("spellbook")};
		m_config = {data_obj.GetDef("config")};
	}
	
	content::operator bool() const
	{
		if (!m_data)
			return false;
		if (!m_data->is<vl::Object>())
			return false;
		return true;
	}
	
	const vl::Var& content::get_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::EmptyVar();
		if (!m_data->is<vl::Object>())
			return vl::EmptyVar();
		auto& data_obj = m_data->as<vl::Object>();
		return *data_obj.Get(field_name);
	}
	
	bool content::has_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::EmptyVar();
		if (!m_data->is<vl::Object>())
			return vl::EmptyVar();
		auto& data_obj = m_data->as<vl::Object>();
		return data_obj.Has(field_name);
	}
	
	bool content::has_data_own(const std::string& field_name) const
	{
		if (!m_data)
			return vl::EmptyVar();
		if (!m_data->is<vl::Object>())
			return vl::EmptyVar();
		auto& data_obj = m_data->as<vl::Object>();
		return data_obj.HasOwn(field_name);
	}
	
	// Field access
	// "spellbook" field
	content::spellbook&  content::get_spellbook()
	{
		return m_spellbook;
	}
	
	const content::spellbook&  content::get_spellbook() const
	{
		return m_spellbook;
	}
	
	// "config" field
	content::config&  content::get_config()
	{
		return m_config;
	}
	
	const content::config&  content::get_config() const
	{
		return m_config;
	}
	
	// "script_links" field
	vl::List& content::script_links()
	{
		return const_cast<vl::List&>(get_script_links()); 
	}
	
	const vl::List& content::get_script_links() const
	{
		static vl::List empty_val = vl::EmptyList();
		if (!m_data)
			return empty_val;
		if (!m_data->is<vl::Object>())
			return empty_val;
		auto& data_obj = m_data->as<vl::Object>();
		auto& data_script_links = data_obj.Get("script_links");
		if (!data_script_links.is<vl::List>())
			return empty_val;
		return data_script_links.as<vl::List>();
	}
	
	// Subclasses definitions begin
	// Initializers
	
	content::spellbook::spellbook(const vl::VarPtr& data)
		: Spellbook(data)
	{
	}
	
	content::spellbook::spellbook(const vl::Var& data)
		: Spellbook(vl::MakePtr(data))
	{
	}
	
	// Initializers
	
	content::config::config(const vl::VarPtr& data)
		: m_data(data)
	{
	}
	
	content::config::config(const vl::Var& data)
		: m_data(vl::MakePtr(data))
	{
	}
	
	content::config::operator bool() const
	{
		if (!m_data)
			return false;
		if (!m_data->is<vl::Object>())
			return false;
		return true;
	}
	
	const vl::Var& content::config::get_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::EmptyVar();
		if (!m_data->is<vl::Object>())
			return vl::EmptyVar();
		auto& data_obj = m_data->as<vl::Object>();
		return *data_obj.Get(field_name);
	}
	
	bool content::config::has_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::EmptyVar();
		if (!m_data->is<vl::Object>())
			return vl::EmptyVar();
		auto& data_obj = m_data->as<vl::Object>();
		return data_obj.Has(field_name);
	}
	
	bool content::config::has_data_own(const std::string& field_name) const
	{
		if (!m_data)
			return vl::EmptyVar();
		if (!m_data->is<vl::Object>())
			return vl::EmptyVar();
		auto& data_obj = m_data->as<vl::Object>();
		return data_obj.HasOwn(field_name);
	}
	
	// Field access
	// "python_spells_directory" field
	const std::string& content::config::python_spells_directory() const
	{
		static std::string empty_val = "";
		if (!m_data)
			return empty_val;
		if (!m_data->is<vl::Object>())
			return empty_val;
		auto& data_obj = m_data->as<vl::Object>();
		auto& data_python_spells_directory = data_obj.Get("python_spells_directory");
		if (!data_python_spells_directory.is<vl::String>())
			return empty_val;
		return data_python_spells_directory.as<vl::String>().Val();
	}
	
	void content::config::set_python_spells_directory(const std::string& value)
	{
		if (!m_data)
			return;
		if (!m_data->is<vl::Object>())
			return;
		auto& data_obj = m_data->as<vl::Object>();
		data_obj.Set("python_spells_directory", value);
	}
	
	// "shell_spells_directory" field
	const std::string& content::config::shell_spells_directory() const
	{
		static std::string empty_val = "";
		if (!m_data)
			return empty_val;
		if (!m_data->is<vl::Object>())
			return empty_val;
		auto& data_obj = m_data->as<vl::Object>();
		auto& data_shell_spells_directory = data_obj.Get("shell_spells_directory");
		if (!data_shell_spells_directory.is<vl::String>())
			return empty_val;
		return data_shell_spells_directory.as<vl::String>().Val();
	}
	
	void content::config::set_shell_spells_directory(const std::string& value)
	{
		if (!m_data)
			return;
		if (!m_data->is<vl::Object>())
			return;
		auto& data_obj = m_data->as<vl::Object>();
		data_obj.Set("shell_spells_directory", value);
	}
	
	// "shell_cmd" field
	const std::string& content::config::shell_cmd() const
	{
		static std::string empty_val = "";
		if (!m_data)
			return empty_val;
		if (!m_data->is<vl::Object>())
			return empty_val;
		auto& data_obj = m_data->as<vl::Object>();
		auto& data_shell_cmd = data_obj.Get("shell_cmd");
		if (!data_shell_cmd.is<vl::String>())
			return empty_val;
		return data_shell_cmd.as<vl::String>().Val();
	}
	
	void content::config::set_shell_cmd(const std::string& value)
	{
		if (!m_data)
			return;
		if (!m_data->is<vl::Object>())
			return;
		auto& data_obj = m_data->as<vl::Object>();
		data_obj.Set("shell_cmd", value);
	}
	
}
