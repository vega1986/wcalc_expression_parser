#include <boost/numeric/conversion/cast.hpp>
#include "generalterm.h"


compile_time_expression_structure::generalTerm::generalTerm(serviceContainer & sc)
    :
      serviceContainer(sc)
{
    std::unique_ptr<generalPrimary> uPtr =
            generalPrimary::createPrimary(sc); // fabric method
    data.emplace_back(interPrimaryOperand::multiply, std::move(uPtr));
    bool primeEnds {false};
    while (true)
    {
        Token t {ts.pop()};
        interPrimaryOperand operand {interPrimaryOperand::undef};
        switch (t.kind) {
            case TokenKind::multiply:
            {
                operand = interPrimaryOperand::multiply;
                break;
            }
            case TokenKind::divide:
            {
                operand = interPrimaryOperand::divide;
                break;
            }
            case TokenKind::mod:
            {
                operand = interPrimaryOperand::mod;
                break;
            }
            default:
            {
                primeEnds = true;
                ts.push(t);
                break;
            }
        }
        if (!primeEnds)
        {
            std::unique_ptr<generalPrimary> prim =
                generalPrimary::createPrimary(sc); // fabric method
            data.emplace_back(operand, std::move(prim));
        }
        else
        {
            break;
        }
    }
}

double compile_time_expression_structure::generalTerm::value() const
{
    using boost::numeric_cast;
    double result {1.0};
    for (const auto& ref : data)
    {

        const auto rightSide {ref.second->value()};
        switch (ref.first)
        {
        case interPrimaryOperand::multiply:
            result *= rightSide;
            break;
        case interPrimaryOperand::divide:
            if (std::abs(rightSide) <= std::numeric_limits<double>::min())
                throw std::logic_error("division by zero");
            result /= ref.second->value();
            break;
        case interPrimaryOperand::mod:
        {
            int i1 = numeric_cast<int>(result);
            double di1 = numeric_cast<double>(i1);
            if (result - di1 > std::numeric_limits<double>::min())
                throw std::logic_error("left operand of %(mod) is not integer");
            int i2 = numeric_cast<int>(rightSide);
            double di2 = numeric_cast<double>(i2);
            if (rightSide - di2 > std::numeric_limits<double>::min())
                throw std::logic_error("right operand of %(mod) is not integer");
            result = i1 % i2;
            break;
        }
        default:
            throw std::logic_error("undefined interPrimaryOperand in generalTerm::value");
        }
    }
    return result;

}
