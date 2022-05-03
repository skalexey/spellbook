#pragma once

#include <string>
#include <vector>
#include <vl_fwd.h>
#include "spell_fwd.h"

namespace spl
{
	class option
	{
	public:
		option() = delete;
		option(vl::Var& data);
		inline const std::string& get_alias() const;
		inline const std::string& get_value() const;

	private:
		vl::VarPtr m_data;
	};

	namespace options
	{
		option_list create_list(const vl::Var& options_data, const args_list& args);
	}
}


