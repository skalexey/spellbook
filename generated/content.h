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
		// Data getter for internal use
		inline const vl::VarPtr& get_data() const {
			return m_data;
		}
		
		// Nested object fields classes
		class spellbook : public Spellbook
		{
		public:
			// Initializers
			spellbook() = default;
			spellbook(const vl::VarPtr& data);
			spellbook(const vl::Var& data);
			// Data validation checker through the bool operator
		};
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
			// Data getter for internal use
			inline const vl::VarPtr& get_data() const {
				return m_data;
			}
			
			// Field access
			// "python_spells_directory" field
			const std::string& python_spells_directory() const;
			void set_python_spells_directory(const std::string& value);
			
			// "shell_spells_directory" field
			const std::string& shell_spells_directory() const;
			void set_shell_spells_directory(const std::string& value);
			
			// "shell_cmd" field
			const std::string& shell_cmd() const;
			void set_shell_cmd(const std::string& value);
			
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
		// "spellbook" field
		spellbook&  get_spellbook();
		const spellbook&  get_spellbook() const;
		
		// "config" field
		config&  get_config();
		const config&  get_config() const;
		
	protected:
		// Data getter for internal use
		inline const vl::VarPtr& _data_() const {
			return m_data;
		}
	
	private:
		// Data members
		class spellbook m_spellbook;
		class config m_config;
		vl::VarPtr m_data;
	};
}
