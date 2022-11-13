#pragma once

#include <vl_fwd.h>

#include "OrderedRegistry.h"

namespace cppgen
{
	class Spell
	{
	public:
		// Initializers
		Spell() = default;
		Spell(const vl::VarPtr& data);
		Spell(const vl::Var& data);
		// Data validation checker through the bool operator
		operator bool() const;
		const vl::Var& get_data(const std::string& field_name) const;
		bool has_data(const std::string& field_name) const;
		bool has_data_own(const std::string& field_name) const;
		// Data getter for internal use
		const vl::VarPtr& get_data() const {
			return m_data;
		}
		
		// Nested object fields classes
		class options : public OrderedRegistry
		{
		public:
			// Initializers
			options() = default;
			options(const vl::VarPtr& data);
			options(const vl::Var& data);
			// Data validation checker through the bool operator
		};
		// Field access
		// "alias" field
		const std::string& alias() const;
		void set_alias(const std::string& value);
		
		// "description" field
		const std::string& description() const;
		void set_description(const std::string& value);
		
		// "options" field
		options&  get_options();
		const options&  get_options() const;
		
		// "rules" field
		const std::string& rules() const;
		void set_rules(const std::string& value);
		
	protected:
		// Data getter for internal use
		const vl::VarPtr& _data_() const {
			return m_data;
		}
	
	private:
		// Data members
		class options m_options;
		vl::VarPtr m_data;
	};
}
