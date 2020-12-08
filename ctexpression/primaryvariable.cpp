#include "primaryvariable.h"



double compile_time_expression_structure::primaryVariable::value()const
{
    const auto it = vars.find(id);
    if (it == cend(vars))
        throw std::logic_error("reference to undefined variable");
    const auto val {it->second};
    return generalPrimary::value(val);
}
