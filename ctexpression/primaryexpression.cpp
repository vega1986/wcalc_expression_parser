#include "generalexpression.h"
#include "primaryexpression.h"


compile_time_expression_structure::primaryExpression::primaryExpression(serviceContainer& sc)
    :
      generalPrimary(), serviceContainer(sc), expr(nullptr)
{
    expr = std::make_unique<generalExpression>(sc);
}

double compile_time_expression_structure::primaryExpression::value() const
{
    if (expr == nullptr)
        throw std::logic_error("null reference to abstractExpression in primaryExpression::value");
    return generalPrimary::value(expr->value());
}
