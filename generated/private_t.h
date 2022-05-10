#pragma once

#include <vl_fwd.h>

namespace cppgen
{
	class private_t
	{
	public:
		// Initializers
		private_t() = default;
		private_t(const vl::VarPtr& data);
		private_t(const vl::Var& data);
		// Data validation checker through the bool operator
		operator bool() const;
		const vl::Var& get_data(const std::string& field_name) const;
		// Data getter for internal use
		inline const vl::VarPtr& get_data() const {
			return m_data;
		}
		
	protected:
		// Data getter for internal use
		inline const vl::VarPtr& _data_() const {
			return m_data;
		}
	
	private:
		// Data members
		vl::VarPtr m_data;
	};
}
