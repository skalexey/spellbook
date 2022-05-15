#pragma once

#include <vl_fwd.h>

namespace cppgen
{
	class OrderedRegistry
	{
	public:
		// Initializers
		OrderedRegistry() = default;
		OrderedRegistry(const vl::VarPtr& data);
		OrderedRegistry(const vl::Var& data);
		// Data validation checker through the bool operator
		operator bool() const;
		const vl::Var& get_data(const std::string& field_name) const;
		// Data getter for internal use
		inline const vl::VarPtr& get_data() const {
			return m_data;
		}
		
		// Nested object fields classes
		class registry
		{
		public:
			// Initializers
			registry() = default;
			registry(const vl::VarPtr& data);
			registry(const vl::Var& data);
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
		// Field access
		// "registry" field
		registry&  get_registry();
		const registry&  get_registry() const;
		
		// "list" field
		vl::List& list();
		const vl::List& get_list() const;
		
	protected:
		// Data getter for internal use
		inline const vl::VarPtr& _data_() const {
			return m_data;
		}
	
	private:
		// Data members
		class registry m_registry;
		vl::VarPtr m_data;
	};
}
