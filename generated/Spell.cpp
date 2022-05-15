#include <vl.h>
#include "Spell.h"

namespace cppgen
{
	// Initializers
	
	Spell::Spell(const vl::VarPtr& data)
		: m_data(data)
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		m_options = {vl::MakePtr(data_obj.Get("options"))};
	}
	
	Spell::Spell(const vl::Var& data)
		: m_data(vl::MakePtr(data))
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		m_options = {vl::MakePtr(data_obj.Get("options"))};
	}
	
	Spell::operator bool() const
	{
		if (!m_data)
			return false;
		if (!m_data->IsObject())
			return false;
		return true;
	}
	
	const vl::Var& Spell::get_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.Get(field_name);
	}
	
	// Field access
	// "alias" field
	const std::string& Spell::alias() const
	{
		static std::string empty_val = "";
		if (!m_data)
			return empty_val;
		if (!m_data->IsObject())
			return empty_val;
		auto& data_obj = m_data->AsObject();
		auto& data_alias = data_obj.Get("alias");
		if (!data_alias.IsString())
			return empty_val;
		return data_alias.AsString().Val();
	}
	
	void Spell::set_alias(const std::string& value)
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		data_obj.Set("alias", value);
	}
	
	// "description" field
	const std::string& Spell::description() const
	{
		static std::string empty_val = "";
		if (!m_data)
			return empty_val;
		if (!m_data->IsObject())
			return empty_val;
		auto& data_obj = m_data->AsObject();
		auto& data_description = data_obj.Get("description");
		if (!data_description.IsString())
			return empty_val;
		return data_description.AsString().Val();
	}
	
	void Spell::set_description(const std::string& value)
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		data_obj.Set("description", value);
	}
	
	// "options" field
	Spell::options&  Spell::get_options()
	{
		return m_options;
	}
	
	const Spell::options&  Spell::get_options() const
	{
		return m_options;
	}
	
	// "rules" field
	const std::string& Spell::rules() const
	{
		static std::string empty_val = "";
		if (!m_data)
			return empty_val;
		if (!m_data->IsObject())
			return empty_val;
		auto& data_obj = m_data->AsObject();
		auto& data_rules = data_obj.Get("rules");
		if (!data_rules.IsString())
			return empty_val;
		return data_rules.AsString().Val();
	}
	
	void Spell::set_rules(const std::string& value)
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		data_obj.Set("rules", value);
	}
	
	// Subclasses definitions begin
	// Initializers
	
	Spell::options::options(const vl::VarPtr& data)
		: OrderedRegistry(data)
	{
	}
	
	Spell::options::options(const vl::Var& data)
		: OrderedRegistry(vl::MakePtr(data))
	{
	}
	
}
