#include <vl.h>
#include "Spellbook.h"

namespace cppgen
{
	// Initializers
	
	Spellbook::Spellbook(const vl::VarPtr& data)
		: m_data(data)
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		m_spells = {vl::MakePtr(data_obj.Get("spells"))};
	}
	
	Spellbook::Spellbook(const vl::Var& data)
		: m_data(vl::MakePtr(data))
	{
		if (!m_data)
			return;
		if (!m_data->IsObject())
			return;
		auto& data_obj = m_data->AsObject();
		m_spells = {vl::MakePtr(data_obj.Get("spells"))};
	}
	
	Spellbook::operator bool() const
	{
		if (!m_data)
			return false;
		if (!m_data->IsObject())
			return false;
		return true;
	}
	
	const vl::Var& Spellbook::get_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.Get(field_name);
	}
	
	bool Spellbook::has_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.Has(field_name);
	}
	
	bool Spellbook::has_data_own(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.HasOwn(field_name);
	}
	
	// Field access
	// "spells" field
	Spellbook::spells&  Spellbook::get_spells()
	{
		return m_spells;
	}
	
	const Spellbook::spells&  Spellbook::get_spells() const
	{
		return m_spells;
	}
	
	// Subclasses definitions begin
	// Initializers
	
	Spellbook::spells::spells(const vl::VarPtr& data)
		: OrderedRegistry(data)
	{
	}
	
	Spellbook::spells::spells(const vl::Var& data)
		: OrderedRegistry(vl::MakePtr(data))
	{
	}
	
}
