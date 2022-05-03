#include "spell_parser.h"
#include "spell_expression.h"

namespace spl
{
    spell_expression_ptr parser::parse(const std::string& s)
    {
        return std::make_shared<spell_expression>(s, args_list());
    }
}