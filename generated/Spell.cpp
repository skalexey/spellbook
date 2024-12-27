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
		if (!m_data->is<vl::Object>())
			return;
		auto& data_obj = m_data->as<vl::Object>();
		m_options = {data_obj.GetDef("options")};
	}
	
	Spell::Spell(const vl::Var& data)
		: m_data(vl::MakePtr(data))
	{
		if (!m_data)
			return;
		if (!m_data->is<vl::Object>())
			return;
		auto& data_obj = m_data->as<vl::Object>();
		m_options = {data_obj.GetDef("options")};
	}
	
	Spell::operator bool() const
	{
		if (!m_data)
			return false;
		if (!m_data->is<vl::Object>())
			return false;
		return true;
	}
	
	const vl::Var& Spell::get_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::EmptyVar();
		if (!m_data->is<vl::Object>())
			return vl::EmptyVar();
		auto& data_obj = m_data->as<vl::Object>();
		return *data_obj.Get(field_name);
	}
	
	bool Spell::has_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::EmptyVar();
		if (!m_data->is<vl::Object>())
			return vl::EmptyVar();
		auto& data_obj = m_data->as<vl::Object>();
		return data_obj.Has(field_name);
	}
	
	bool Spell::has_data_own(const std::string& field_name) const
	{
		if (!m_data)
			return vl::EmptyVar();
		if (!m_data->is<vl::Object>())
			return vl::EmptyVar();
		auto& data_obj = m_data->as<vl::Object>();
		return data_obj.HasOwn(field_name);
	}
	
	// Field access
	// "rules" field
	const std::string& Spell::rules() const
	{
		static std::string empty_val = "";
		if (!m_data)
			return empty_val;
		if (!m_data->is<vl::Object>())
			return empty_val;
		auto& data_obj = m_data->as<vl::Object>();
		auto& data_rules = data_obj.Get("rules");
		if (!data_rules.is<vl::String>())
			return empty_val;
		return data_rules.as<vl::String>().Val();
	}
	
	void Spell::set_rules(const std::string& value)
	{
		if (!m_data)
			return;
		if (!m_data->is<vl::Object>())
			return;
		auto& data_obj = m_data->as<vl::Object>();
		data_obj.Set("rules", value);
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
	
	// "description" field
	const std::string& Spell::description() const
	{
		static std::string empty_val = "";
		if (!m_data)
			return empty_val;
		if (!m_data->is<vl::Object>())
			return empty_val;
		auto& data_obj = m_data->as<vl::Object>();
		auto& data_description = data_obj.Get("description");
		if (!data_description.is<vl::String>())
			return empty_val;
		return data_description.as<vl::String>().Val();
	}
	
	void Spell::set_description(const std::string& value)
	{
		if (!m_data)
			return;
		if (!m_data->is<vl::Object>())
			return;
		auto& data_obj = m_data->as<vl::Object>();
		data_obj.Set("description", value);
	}
	
	// "alias" field
	const std::string& Spell::alias() const
	{
		static std::string empty_val = "";
		if (!m_data)
			return empty_val;
		if (!m_data->is<vl::Object>())
			return empty_val;
		auto& data_obj = m_data->as<vl::Object>();
		auto& data_alias = data_obj.Get("alias");
		if (!data_alias.is<vl::String>())
			return empty_val;
		return data_alias.as<vl::String>().Val();
	}
	
	void Spell::set_alias(const std::string& value)
	{
		if (!m_data)
			return;
		if (!m_data->is<vl::Object>())
			return;
		auto& data_obj = m_data->as<vl::Object>();
		data_obj.Set("alias", value);
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
