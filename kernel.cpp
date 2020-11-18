#include <cmath>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include "kernel.h"

const std::map<std::string, double> calculator::WExpression::global_constants
{
    {"pi", boost::math::constants::pi<double>()},
    {"e", boost::math::constants::e<double>()}
};

double calculator::WExpression::expression()
{
    Token t {ts.pop()};
    bool isNeg {false};
    if (t.kind == TokenKind::minus)
        isNeg = true;
    else if (t.kind == TokenKind::plus)
        isNeg = false;
    else
        ts.push(t);

    double left {term()};
    if (isNeg) left = -left;

    while (true)
    {
        Token t {ts.pop()};
        switch(t.kind)
        {
            case TokenKind::plus:
                left += term();
                break;
            case TokenKind::minus:
                left -= term();
                break;
            default:
                ts.push(t);
                return left;
        }
    }
}

double calculator::WExpression::term()
{
    using boost::numeric_cast;
    double left {primary()};

    while (true)
    {
        Token t {ts.pop()};
        switch (t.kind) {
            case TokenKind::multiply:
                left *= primary();
                break;
            case TokenKind::divide:
            {
                double d {primary()};
                if (d == 0.0) throw std::logic_error("division by 0");
                left /= d;
                break;
            }
            case TokenKind::mod:
            {
                double d{primary()};
                int i1 = numeric_cast<int>(left);
                double di1 = numeric_cast<double>(i1);
                if (left - di1 > std::numeric_limits<double>::min())
                    throw std::logic_error("left operand of %(mod) is not integer");
                int i2 = numeric_cast<int>(d);
                double di2 = numeric_cast<double>(i2);
                if (d - di2 > std::numeric_limits<double>::min())
                    throw std::logic_error("right operand of %(mod) is not integer");
                left = i1 % i2;
                break;
            }
            default:
                ts.push(t);
                return left;
        }
    }
}

double calculator::WExpression::primary()
{
    using boost::numeric_cast;
    double result {0.0};
    Token t {ts.pop()};
    auto endBracket = [](TokenKind tk)->TokenKind{
        switch (tk)
        {
            case TokenKind::bracket_left0:
                return TokenKind::bracket_right0;
            case TokenKind::bracket_left1:
                return TokenKind::bracket_right1;
            default:
                return tk;
        }
    };
    switch (t.kind) {
        case TokenKind::number:
        {
            result = t.value;
            break;
        }
        case TokenKind::variable:
        {
            // first find in constants
            auto gcit {global_constants.find(t.name)};
            if (gcit == cend(global_constants))
            {
                auto vit = variables.find(t.name);
                if (vit == cend(variables))
                {
                    throw std::logic_error("undefined symbolic literal " + t.name);
                }
                result = vit->second;
                break;
            }
            result = gcit->second;
            break;
//            auto it {variables.find(t.name)};
//            if (it == end(variables))
//                throw std::logic_error("undefined variable "+t.name);
//            result = it->second;
//            break;
        }
        case TokenKind::function:
        {
            result = function(t.name);
            break;
        }
        case TokenKind::bracket_left0:
        case TokenKind::bracket_left1:
        {
            double d {expression()};
            Token t2 {ts.pop()};
            if (t2.kind != endBracket(t.kind)/*TokenKind::bracket_right0*/)
                throw std::logic_error("bracket_right expected");
            result = d;
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
    while (true)
    {
        Token tp {ts.pop()};
        switch (tp.kind)
        {
            case TokenKind::factorial:
            {
                unsigned int f = numeric_cast<unsigned int>(result);
                double df = numeric_cast<double>(f);
                if (result-df > std::numeric_limits<double>::min())
                    throw std::logic_error("factorial applied to not integer");
                result = boost::math::factorial<double>(f);
                break;
            }
            default:
            {
                ts.push(tp);
                return result;
            }
        }
    }
//    return result;
//    switch (tf.kind)
//    {
//        case TokenKind::factorial:
//        {
//            unsigned int f = numeric_cast<unsigned int>(result);
//            double df = numeric_cast<double>(f);
//            if (result-df > std::numeric_limits<double>::min())
//                throw std::logic_error("factorial applied to not integer");
//            return boost::math::factorial<double>(f);
//        }
//        default:
//            ts.push(tf);
//            return result;
    //    }
}

double calculator::WExpression::function(std::string function_name)
{
//    double result {0.0};
    Token t {ts.pop()};
    std::vector<double> args;
    auto endBracket = [](TokenKind tk)->TokenKind{
        switch (tk)
        {
            case TokenKind::bracket_left0:
                return TokenKind::bracket_right0;
            case TokenKind::bracket_left1:
                return TokenKind::bracket_right1;
            default:
                return tk;
        }
    };
    switch (t.kind)
    {
        case TokenKind::bracket_left0:
        case TokenKind::bracket_left1:
        {
            while (ist)
            {
                double d {expression()};
                args.push_back(d);
                Token t2 {ts.pop()};
                if (t2.kind != TokenKind::comma)
                {
                    ts.push(t2);
                    break;
                }
            } // args is done
            Token t3 {ts.pop()};
            if (t3.kind != endBracket(t.kind))
                throw std::logic_error("correct bracket_right is expected");
            break;
        }
        default:
            throw std::logic_error("bracket_left is expected");
    }
    if (function_name == "pow")
    {
        if (args.size() != 2)
            throw std::logic_error("2 args for pow function");
        return std::pow(args[0], args[1]);
    }
    else if (function_name == "cos")
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for cos function");
        return std::cos(args[0]);
    }
    else if (function_name == "sin")
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for sin function");
        return std::sin(args[0]);
    }
    else if (function_name == "tan")
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for tan function");
        return std::tan(args[0]);
    }
    else if (function_name == "acos")
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for acos function");
        if (abs(args[0])>1)
            throw std::logic_error("bad argument for acos");
        return std::acos(args[0]);
    }
    else if (function_name == "asin")
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for asin function");
        if (abs(args[0])>1)
            throw std::logic_error("bad argument for asin");
        return std::asin(args[0]);
    }
    else if (function_name == "atan")
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for atan function");
        return std::atan(args[0]);
    }
    else if (function_name == "atan2")
    {
        if (args.size() != 2)
            throw std::logic_error("2 args for atan2 function");
        return std::atan2(args[0], args[1]);
    }
    else if (function_name == "exp")
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for exp function");
        return std::exp(args[0]);
    }
    else if (function_name == "log")
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for log function");
        if ((args[0])<0)
            throw std::logic_error("bad argument for log");
        return std::log(args[0]);
    }
    else if (function_name == "log10")
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for log10 function");
        if ((args[0])<0)
            throw std::logic_error("bad argument for log10");
        return std::log10(args[0]);
    }
    else if (function_name == "sqrt")
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for sqrt function");
        if ((args[0])<0)
            throw std::logic_error("bad argument for sqrt");
        return std::sqrt(args[0]);
    }
    else if (function_name == "abs")
    {
        if (args.size() != 1)
            throw std::logic_error("1 args for abs function");
        return std::fabs(args[0]);
    }
    else
    {
        throw std::logic_error("undefined function"+function_name);
    }


}

calculator::Token calculator::Token_stream::pop()
{
    if (!(data.empty()))
    {
        auto res = data.top();
        data.pop();
        return res;
    }
    Token result;
    if (!ist) return result;
    char sym {0};
    ist >> sym;
    if (ist.eof()) return result;
    switch (sym)
    {
        case '(':
            result.kind = TokenKind::bracket_left0;
            break;
        case ')':
            result.kind = TokenKind::bracket_right0;
            break;
        case '{':
            result.kind = TokenKind::bracket_left1;
            break;
        case '}':
            result.kind = TokenKind::bracket_right1;
            break;
        case '*':
            result.kind = TokenKind::multiply;
            break;
        case '/':
            result.kind = TokenKind::divide;
            break;
        case '%':
            result.kind = TokenKind::mod;
            break;
        case '+':
            result.kind = TokenKind::plus;
            break;
        case '-':
            result.kind = TokenKind::minus;
            break;
        case '!':
            result.kind = TokenKind::factorial;
            break;
        case ',':
            result.kind = TokenKind::comma;
            break;
        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            ist.unget();
            double val {0.0};
            ist >> val;
            result.kind = TokenKind::number;
            result.value = val;
            break;
        }
        default:
        {
            if (isalpha(sym)) // function or variable name: func ( | lsldkm239283
            {
                std::string s;
                s += sym;
                char ch {0};
                while (ist.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
                ist.putback(ch);
                ist >> ch;
                if (ch == '(' || ch == '{')
                {
                    ist.putback(ch);
                    result.kind = TokenKind::function;
                    result.name = s;
                    break;
                }
                else
                {
                    ist.putback(ch);
                    result.kind = TokenKind::variable;
                    result.name = s;
                    break;
                }
            }
            else
            {
                throw std::logic_error("bad Token");
            }
        }
    }
    return result;
}
