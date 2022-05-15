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
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		m_config = {vl::MakePtr(data_obj.Get("config"))};
		m_spellbook = {vl::MakePtr(data_obj.Get("spellbook"))};
	}
	
	content::content(const vl::Var& data)
		: m_data(vl::MakePtr(data))
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		m_config = {vl::MakePtr(data_obj.Get("config"))};
		m_spellbook = {vl::MakePtr(data_obj.Get("spellbook"))};
	}
	
	content::operator bool() const
	{
		if (!m_data)
			return false;
		if (!m_data->IsObject())
			return false;
		return true;
	}
	
	const vl::Var& content::get_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.Get(field_name);
	}
	
	// Field access
	// "config" field
	content::config&  content::get_config()
	{
		return m_config;
	}
	
	const content::config&  content::get_config() const
	{
		return m_config;
	}
	
	// "spellbook" field
	content::spellbook&  content::get_spellbook()
	{
		return m_spellbook;
	}
	
	const content::spellbook&  content::get_spellbook() const
	{
		return m_spellbook;
	}
	
	// Subclasses definitions begin
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
		if (!m_data->IsObject())
			return false;
		return true;
	}
	
	const vl::Var& content::config::get_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.Get(field_name);
	}
	
	// Field access
	// "python_spells_directory" field
	const std::string& content::config::python_spells_directory() const
	{
		static std::string empty_val = "";
		if (!m_data)
			return empty_val;
		if (!m_data->IsObject())
			return empty_val;
		auto& data_obj = m_data->AsObject();
		auto& data_python_spells_directory = data_obj.Get("python_spells_directory");
		if (!data_python_spells_directory.IsString())
			return empty_val;
		return data_python_spells_directory.AsString().Val();
	}
	
	void content::config::set_python_spells_directory(const std::string& value)
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		data_obj.Set("python_spells_directory", value);
	}
	
	// Initializers
	
	content::spellbook::spellbook(const vl::VarPtr& data)
		: Spellbook(data)
	{
	}
	
	content::spellbook::spellbook(const vl::Var& data)
		: Spellbook(vl::MakePtr(data))
	{
	}
	
}
