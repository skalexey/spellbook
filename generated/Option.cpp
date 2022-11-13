#include <vl.h>
#include "Option.h"

namespace cppgen
{
	// Initializers
	
	Option::Option(const vl::VarPtr& data)
		: m_data(data)
	{
	}
	
	Option::Option(const vl::Var& data)
		: m_data(vl::MakePtr(data))
	{
	}
	
	Option::operator bool() const
	{
		if (!m_data)
			return false;
		if (!m_data->IsObject())
			return false;
		return true;
	}
	
	const vl::Var& Option::get_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.Get(field_name);
	}
	
	bool Option::has_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.Has(field_name);
	}
	
	bool Option::has_data_own(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.HasOwn(field_name);
	}
	
	// Field access
	// "alias" field
	const std::string& Option::alias() const
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
	
	void Option::set_alias(const std::string& value)
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		data_obj.Set("alias", value);
	}
	
	// "value" field
	const std::string& Option::value() const
	{
		static std::string empty_val = "";
		if (!m_data)
			return empty_val;
		if (!m_data->IsObject())
			return empty_val;
		auto& data_obj = m_data->AsObject();
		auto& data_value = data_obj.Get("value");
		if (!data_value.IsString())
			return empty_val;
		return data_value.AsString().Val();
	}
	
	void Option::set_value(const std::string& value)
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		data_obj.Set("value", value);
	}
	
	// "description" field
	const std::string& Option::description() const
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
	
	void Option::set_description(const std::string& value)
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		data_obj.Set("description", value);
	}
	
	// "title" field
	const std::string& Option::title() const
	{
		static std::string empty_val = "";
		if (!m_data)
			return empty_val;
		if (!m_data->IsObject())
			return empty_val;
		auto& data_obj = m_data->AsObject();
		auto& data_title = data_obj.Get("title");
		if (!data_title.IsString())
			return empty_val;
		return data_title.AsString().Val();
	}
	
	void Option::set_title(const std::string& value)
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		data_obj.Set("title", value);
	}
	
	// "default_value" field
	const std::string& Option::default_value() const
	{
		static std::string empty_val = "";
		if (!m_data)
			return empty_val;
		if (!m_data->IsObject())
			return empty_val;
		auto& data_obj = m_data->AsObject();
		auto& data_default_value = data_obj.Get("default_value");
		if (!data_default_value.IsString())
			return empty_val;
		return data_default_value.AsString().Val();
	}
	
	void Option::set_default_value(const std::string& value)
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		data_obj.Set("default_value", value);
	}
	
}
