#include <vl.h>
#include "private_t.h"

namespace cppgen
{
	// Initializers
	
	private_t::private_t(const vl::VarPtr& data)
		: m_data(data)
	{
	}
	
	private_t::private_t(const vl::Var& data)
		: m_data(vl::MakePtr(data))
	{
	}
	
	private_t::operator bool() const
	{
		if (!m_data)
			return false;
		if (!m_data->IsObject())
			return false;
		return true;
	}
	
	const vl::Var& private_t::get_data(const std::string& field_name) const
	{
		if (!m_data)
			return vl::emptyVar;
		if (!m_data->IsObject())
			return vl::emptyVar;
		auto& data_obj = m_data->AsObject();
		return data_obj.Get(field_name);
	}
	
}
