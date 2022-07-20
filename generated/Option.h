#pragma once

#include <vl_fwd.h>

namespace cppgen
{
	class Option
	{
	public:
		// Initializers
		Option() = default;
		Option(const vl::VarPtr& data);
		Option(const vl::Var& data);
		// Data validation checker through the bool operator
		operator bool() const;
		const vl::Var& get_data(const std::string& field_name) const;
		bool has_data(const std::string& field_name) const;
		bool has_data_own(const std::string& field_name) const;
		// Data getter for internal use
		inline const vl::VarPtr& get_data() const {
			return m_data;
		}
		
		// Field access
		// "default_value" field
		const std::string& default_value() const;
		void set_default_value(const std::string& value);
		
		// "title" field
		const std::string& title() const;
		void set_title(const std::string& value);
		
		// "description" field
		const std::string& description() const;
		void set_description(const std::string& value);
		
		// "value" field
		const std::string& value() const;
		void set_value(const std::string& value);
		
		// "alias" field
		const std::string& alias() const;
		void set_alias(const std::string& value);
		
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
