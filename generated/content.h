#pragma once

#include <vl_fwd.h>

#include "Spellbook.h"

namespace cppgen
{
	class content
	{
	public:
		// Initializers
		content() = default;
		content(const vl::VarPtr& data);
		content(const vl::Var& data);
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
		class config
		{
		public:
			// Initializers
			config() = default;
			config(const vl::VarPtr& data);
			config(const vl::Var& data);
			// Data validation checker through the bool operator
			operator bool() const;
			const vl::Var& get_data(const std::string& field_name) const;
			bool has_data(const std::string& field_name) const;
			bool has_data_own(const std::string& field_name) const;
			// Data getter for internal use
			const vl::VarPtr& get_data() const {
				return m_data;
			}
			
			// Field access
			// "shell_cmd" field
			const std::string& shell_cmd() const;
			void set_shell_cmd(const std::string& value);
			
			// "shell_spells_directory" field
			const std::string& shell_spells_directory() const;
			void set_shell_spells_directory(const std::string& value);
			
			// "python_spells_directory" field
			const std::string& python_spells_directory() const;
			void set_python_spells_directory(const std::string& value);
			
		protected:
			// Data getter for internal use
			const vl::VarPtr& _data_() const {
				return m_data;
			}
		
		private:
			// Data members
			vl::VarPtr m_data;
		};
		class spellbook : public Spellbook
		{
		public:
			// Initializers
			spellbook() = default;
			spellbook(const vl::VarPtr& data);
			spellbook(const vl::Var& data);
			// Data validation checker through the bool operator
		};
		// Field access
		// "script_links" field
		vl::List& script_links();
		const vl::List& get_script_links() const;
		
		// "config" field
		config&  get_config();
		const config&  get_config() const;
		
		// "spellbook" field
		spellbook&  get_spellbook();
		const spellbook&  get_spellbook() const;
		
	protected:
		// Data getter for internal use
		const vl::VarPtr& _data_() const {
			return m_data;
		}
	
	private:
		// Data members
		class config m_config;
		class spellbook m_spellbook;
		vl::VarPtr m_data;
	};
}
