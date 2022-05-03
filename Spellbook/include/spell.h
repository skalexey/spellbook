#pragma once
#include <string>
#include "spell_options.h"
#include "spell_fwd.h"
#include <vl_fwd.h>

namespace spl
{
	class spell
	{
	public:
		spell(const vl::VarPtr& data);
		virtual bool cast(const option_list& options);
		const std::string& get_alias() const;

	protected:

	private:
		vl::VarPtr m_data;
	};
}

