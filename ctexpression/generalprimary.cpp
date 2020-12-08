#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include "generalprimary.h"
#include "primarynumber.h"
#include "primaryvariable.h"
#include "servicecontainer.h"
#include "primaryfunction.h"
#include "primaryexpression.h"



double compile_time_expression_structure::generalPrimary::value(double prime) const
{
    if (isFactorial)
    {
        if (prime<0.0)
            throw std::logic_error("factorial applied to neg. value");
        using boost::numeric_cast;
        unsigned int uif = numeric_cast<unsigned int>(prime);
        double duif = numeric_cast<double>(uif);
        if (prime-duif > std::numeric_limits<double>::min())
            throw std::logic_error("factorial applied to not integer value");
        return boost::math::factorial<double>(uif);
    }
    else
    {   
        return prime;
    }
}

std::unique_ptr<compile_time_expression_structure::generalPrimary>
compile_time_expression_structure::generalPrimary::createPrimary
(compile_time_expression_structure::serviceContainer& sc)
{
    Token t {sc.pop()};
    std::unique_ptr<generalPrimary> gp{nullptr};
    switch (t.kind) {
        case TokenKind::number:
        {
            gp = std::make_unique<primaryNumber>(t.value);
            break;
        }
        case TokenKind::variable:
        {
            // first find in constants
            auto gcit {global_constants_id.find(t.name)};
            if (gcit == cend(global_constants_id))
            {
                auto vit {global_variables_id.find(t.name)};
                if (vit == cend(global_variables_id))
                    throw std::logic_error("undefined variable literal " + t.name);
                // not constant
                gp = std::make_unique<primaryVariable>(vit->second, sc);
                break;
            }
            auto cit = global_constants.find(gcit->second);
            if (cit == cend(global_constants))
                throw std::logic_error("undefined symbolic literal");
            const double Value = cit->second;
            gp = std::make_unique<primaryNumber>(Value);
            break;
        }
        case TokenKind::function:
        {
            auto gfidIt {global_functions_id.find(t.name)};
            if (gfidIt == cend(global_functions_id))
                throw std::logic_error("unknown function name");
            gp = std::make_unique<primaryFunction>(gfidIt->second, sc);
            break;
        }
        case TokenKind::bracket_left0:
//        case TokenKind::bracket_left1:
        {
            gp = std::make_unique<primaryExpression>(sc);
            //double d {expression(ist)};
            Token t2 {sc.pop()};
            if (t2.kind != TokenKind::bracket_right0)
                throw std::logic_error("bracket_right expected");
            break;
        }
//        case TokenKind::bracket_left1:
//        {
//            double d {expression()};
//            t = ts.pop();
//            if (t.kind != TokenKind::bracket_right1)
//                throw std::logic_error("bracket_right expected");
//            result = d;
//            break;
//        }
        default:
            throw std::logic_error("primary is expected");
    }

    Token tp {sc.pop()};
    if (tp.kind == TokenKind::factorial)
    {
        gp->setFactorial(true);
    }
    else {
        sc.push(tp);
    }
    return gp;
}


