#include <cmath>
#include "primaryfunction.h"
#include "generalexpression.h"

compile_time_expression_structure::primaryFunction::primaryFunction(functionId _id, serviceContainer &sc)
    :
    serviceContainer (sc),id(_id)
{
    Token t {sc.pop()};
    switch (t.kind)
    {
        case TokenKind::bracket_left0:
//        case TokenKind::bracket_left1:
        {
            while (true)
            {
                std::unique_ptr<abstractExpression> ge =
                        std::make_unique<generalExpression>(sc);
                args.emplace_back(std::move(ge));
                Token t2 {sc.pop()};
                if (t2.kind != TokenKind::comma)
                {
                    ts.push(t2);
                    break;
                }
            } // args is done
            Token t3 {ts.pop()};
            if (t3.kind != TokenKind::bracket_right0)
                throw std::logic_error("correct bracket_right is expected");
            break;
        }
        default:
            throw std::logic_error("bracket_left is expected");
    }

}

double compile_time_expression_structure::primaryFunction::value() const
{
    double result {0.0};

    switch (id)
    {
    case functionId::pow:
    {
        if (args.size() != 2)
            throw std::logic_error("2 args for pow function");
        result = std::pow(args[0]->value(), args[1]->value());
        break;
    }
    case functionId::cos:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for cos function");
        result = std::cos(args[0]->value());
        break;
    }
    case functionId::sin:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for sin function");
        result = std::sin(args[0]->value());
        break;
    }
    case functionId::tan:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for tan function");
        result = std::tan(args[0]->value());
        break;
    }
    case functionId::acos:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for acos function");
        result = std::acos(args[0]->value());
        break;
    }
    case functionId::asin:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for asin function");
        result = std::asin(args[0]->value());
        break;
    }
    case functionId::atan:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for atan function");
        result = std::atan(args[0]->value());
        break;
    }
    case functionId::atan2:
    {
        if (args.size() != 2)
            throw std::logic_error("2 args for atan function");
        result = std::atan2(args[0]->value(), args[1]->value());
        break;
    }
    case functionId::exp:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for exp function");
        result = std::exp(args[0]->value());
        break;
    }
    case functionId::log:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for log function");
        result = std::log(args[0]->value());
        break;
    }
    case functionId::log10:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for log10 function");
        result = std::log10(args[0]->value());
        break;
    }
    case functionId::sqrt:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for sqrt function");
        result = std::sqrt(args[0]->value());
        break;
    }
    case functionId::abs:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for abs function");
        result = std::fabs(args[0]->value());
        break;
    }
    case functionId::round:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for round function");
        result = std::round(args[0]->value());
        break;
    }
    case functionId::floor:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for floor function");
        retult = std::floor(args[0]->value());
        break;
    }
    case functionId::ceil:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for ceil function");
        retult = std::ceil(args[0]->value());
        break;
    }
    case functionId::trunc:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for trunc function");
        retult = std::trunc(args[0]->value());
        break;
    }
    case functionId::sinh:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for sinh function");
        retult = std::sinh(args[0]->value());
        break;
    }    
    case functionId::cosh:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for cosh function");
        retult = std::cosh(args[0]->value());
        break;
    }    
    case functionId::tanh:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for tanh function");
        retult = std::tanh(args[0]->value());
        break;
    }    
    case functionId::asinh:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for asinh function");
        retult = std::asinh(args[0]->value());
        break;
    }
    case functionId::acosh:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for acosh function");
        retult = std::acosh(args[0]->value());
        break;
    }
    case functionId::atanh:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for atanh function");
        retult = std::atanh(args[0]->value());
        break;
    }
    case functionId::degrees:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for degrees function");
        retult = std::degrees(args[0]->value());
        break;
    }
    case functionId::radians:
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for radians function");
        retult = std::radians(args[0]->value());
        break;
    }
    default:
    {
        throw std::logic_error("undefined function");
    }

    }
    return generalPrimary::value(result);
}
