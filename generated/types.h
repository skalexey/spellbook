#pragma once

#include <vl_fwd.h>

#include "Option.h"
#include "OrderedRegistry.h"
#include "Spell.h"
#include "Spellbook.h"

namespace cppgen
{
	class types
	{
	public:
		// Initializers
		types() = default;
		types(const vl::VarPtr& data);
		types(const vl::Var& data);
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
		// "OrderedRegistry" field
		OrderedRegistry&  get_OrderedRegistry();
		const OrderedRegistry&  get_OrderedRegistry() const;
		
		// "Spellbook" field
		Spellbook&  get_Spellbook();
		const Spellbook&  get_Spellbook() const;
		
		// "Option" field
		Option&  get_Option();
		const Option&  get_Option() const;
		
		// "Spell" field
		Spell&  get_Spell();
		const Spell&  get_Spell() const;
		
	protected:
		// Data getter for internal use
		inline const vl::VarPtr& _data_() const {
			return m_data;
		}
	
	private:
		// Data members
		class OrderedRegistry m_OrderedRegistry;
		class Spellbook m_Spellbook;
		class Option m_Option;
		class Spell m_Spell;
		vl::VarPtr m_data;
	};
}
