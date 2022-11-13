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
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		m_registry = {vl::MakePtr(data_obj.Get("registry"))};
	}
	
	OrderedRegistry::OrderedRegistry(const vl::Var& data)
		: m_data(vl::MakePtr(data))
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		m_registry = {vl::MakePtr(data_obj.Get("registry"))};
	}
	
	OrderedRegistry::operator bool() const
	{
		if (!m_data)
			return false;
		if (!m_data->IsObject())
			return false;
		return true;
	}
	
	const vl::Var& OrderedRegistry::get_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.Get(field_name);
	}
	
	bool OrderedRegistry::has_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.Has(field_name);
	}
	
	bool OrderedRegistry::has_data_own(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.HasOwn(field_name);
	}
	
	// Field access
	// "registry" field
	OrderedRegistry::registry&  OrderedRegistry::get_registry()
	{
		return m_registry;
	}
	
	const OrderedRegistry::registry&  OrderedRegistry::get_registry() const
	{
		return m_registry;
	}
	
	// "list" field
	vl::List& OrderedRegistry::list()
	{
		return const_cast<vl::List&>(get_list()); 
	}
	
	const vl::List& OrderedRegistry::get_list() const
	{
		static vl::List empty_val = vl::emptyList;
		if (!m_data)
			return empty_val;
		if (!m_data->IsObject())
			return empty_val;
		auto& data_obj = m_data->AsObject();
		auto& data_list = data_obj.Get("list");
		if (!data_list.IsList())
			return empty_val;
		return data_list.AsList();
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
		if (!m_data->IsObject())
			return false;
		return true;
	}
	
	const vl::Var& OrderedRegistry::registry::get_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.Get(field_name);
	}
	
	bool OrderedRegistry::registry::has_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.Has(field_name);
	}
	
	bool OrderedRegistry::registry::has_data_own(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.HasOwn(field_name);
	}
	
}
