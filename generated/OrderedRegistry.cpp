#include <vl.h>
#include "OrderedRegistry.h"

namespace cppgen
{
	// Initializers
	
	OrderedRegistry::OrderedRegistry(const vl::VarPtr& data)
		: m_data(data)
	{
		if (!m_data)
			return;
		if (!m_data->is<vl::Object>())
			return;
		auto& data_obj = m_data->as<vl::Object>();
		m_registry = {data_obj.GetDef("registry")};
	}
	
	OrderedRegistry::OrderedRegistry(const vl::Var& data)
		: m_data(vl::MakePtr(data))
	{
		if (!m_data)
			return;
		if (!m_data->is<vl::Object>())
			return;
		auto& data_obj = m_data->as<vl::Object>();
		m_registry = {data_obj.GetDef("registry")};
	}
	
	OrderedRegistry::operator bool() const
	{
		if (!m_data)
			return false;
		if (!m_data->is<vl::Object>())
			return false;
		return true;
	}
	
	const vl::Var& OrderedRegistry::get_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::EmptyVar();
		if (!m_data->is<vl::Object>())
			return vl::EmptyVar();
		auto& data_obj = m_data->as<vl::Object>();
		return *data_obj.Get(field_name);
	}
	
	bool OrderedRegistry::has_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::EmptyVar();
		if (!m_data->is<vl::Object>())
			return vl::EmptyVar();
		auto& data_obj = m_data->as<vl::Object>();
		return data_obj.Has(field_name);
	}
	
	bool OrderedRegistry::has_data_own(const std::string& field_name) const
	{
		if (!m_data)
			return vl::EmptyVar();
		if (!m_data->is<vl::Object>())
			return vl::EmptyVar();
		auto& data_obj = m_data->as<vl::Object>();
		return data_obj.HasOwn(field_name);
	}
	
	// Field access
	// "list" field
	vl::List& OrderedRegistry::list()
	{
		return const_cast<vl::List&>(get_list()); 
	}
	
	const vl::List& OrderedRegistry::get_list() const
	{
		static vl::List empty_val = vl::EmptyList();
		if (!m_data)
			return empty_val;
		if (!m_data->is<vl::Object>())
			return empty_val;
		auto& data_obj = m_data->as<vl::Object>();
		auto& data_list = data_obj.Get("list");
		if (!data_list.is<vl::List>())
			return empty_val;
		return data_list.as<vl::List>();
	}
	
	// "registry" field
	OrderedRegistry::registry&  OrderedRegistry::get_registry()
	{
		return m_registry;
	}
	
	const OrderedRegistry::registry&  OrderedRegistry::get_registry() const
	{
		return m_registry;
	}
	
	// Subclasses definitions begin
	// Initializers
	
	OrderedRegistry::registry::registry(const vl::VarPtr& data)
		: m_data(data)
	{
	}
	
	OrderedRegistry::registry::registry(const vl::Var& data)
		: m_data(vl::MakePtr(data))
	{
	}
	
	OrderedRegistry::registry::operator bool() const
	{
		if (!m_data)
			return false;
		if (!m_data->is<vl::Object>())
			return false;
		return true;
	}
	
	const vl::Var& OrderedRegistry::registry::get_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::EmptyVar();
		if (!m_data->is<vl::Object>())
			return vl::EmptyVar();
		auto& data_obj = m_data->as<vl::Object>();
		return *data_obj.Get(field_name);
	}
	
	bool OrderedRegistry::registry::has_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::EmptyVar();
		if (!m_data->is<vl::Object>())
			return vl::EmptyVar();
		auto& data_obj = m_data->as<vl::Object>();
		return data_obj.Has(field_name);
	}
	
	bool OrderedRegistry::registry::has_data_own(const std::string& field_name) const
	{
		if (!m_data)
			return vl::EmptyVar();
		if (!m_data->is<vl::Object>())
			return vl::EmptyVar();
		auto& data_obj = m_data->as<vl::Object>();
		return data_obj.HasOwn(field_name);
	}
	
}
