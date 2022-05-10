#include <vl.h>
#include "types.h"

namespace cppgen
{
	// Initializers
	
	types::types(const vl::VarPtr& data)
		: m_data(data)
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		m_OrderedRegistry = {vl::MakePtr(data_obj.Get("OrderedRegistry"))};
		m_Option = {vl::MakePtr(data_obj.Get("Option"))};
		m_Spellbook = {vl::MakePtr(data_obj.Get("Spellbook"))};
		m_Spell = {vl::MakePtr(data_obj.Get("Spell"))};
	}
	
	types::types(const vl::Var& data)
		: m_data(vl::MakePtr(data))
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		m_OrderedRegistry = {vl::MakePtr(data_obj.Get("OrderedRegistry"))};
		m_Option = {vl::MakePtr(data_obj.Get("Option"))};
		m_Spellbook = {vl::MakePtr(data_obj.Get("Spellbook"))};
		m_Spell = {vl::MakePtr(data_obj.Get("Spell"))};
	}
	
	types::operator bool() const
	{
		if (!m_data)
			return false;
		if (!m_data->IsObject())
			return false;
		return true;
	}
	
	const vl::Var& types::get_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.Get(field_name);
	}
	
	// Field access
	// "OrderedRegistry" field
	OrderedRegistry&  types::get_OrderedRegistry()
	{
		return m_OrderedRegistry;
	}
	
	const OrderedRegistry&  types::get_OrderedRegistry() const
	{
		return m_OrderedRegistry;
	}
	
	// "Option" field
	Option&  types::get_Option()
	{
		return m_Option;
	}
	
	const Option&  types::get_Option() const
	{
		return m_Option;
	}
	
	// "Spellbook" field
	Spellbook&  types::get_Spellbook()
	{
		return m_Spellbook;
	}
	
	const Spellbook&  types::get_Spellbook() const
	{
		return m_Spellbook;
	}
	
	// "Spell" field
	Spell&  types::get_Spell()
	{
		return m_Spell;
	}
	
	const Spell&  types::get_Spell() const
	{
		return m_Spell;
	}
	
}
