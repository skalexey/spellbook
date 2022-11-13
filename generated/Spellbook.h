#pragma once

#include <vl_fwd.h>

#include "OrderedRegistry.h"

namespace cppgen
{
	class Spellbook
	{
	public:
		// Initializers
		Spellbook() = default;
		Spellbook(const vl::VarPtr& data);
		Spellbook(const vl::Var& data);
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
		class spells : public OrderedRegistry
		{
		public:
			// Initializers
			spells() = default;
			spells(const vl::VarPtr& data);
			spells(const vl::Var& data);
			// Data validation checker through the bool operator
		};
		// Field access
		// "spells" field
		spells&  get_spells();
		const spells&  get_spells() const;
		
	protected:
		// Data getter for internal use
		const vl::VarPtr& _data_() const {
			return m_data;
		}
	
	private:
		// Data members
		class spells m_spells;
		vl::VarPtr m_data;
	};
}
