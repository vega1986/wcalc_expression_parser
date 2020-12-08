#include "generalexpression.h"
#include "generalterm.h"




void compile_time_expression_structure::generalExpression::initialize()
{
    using namespace std;
    Token t {ts.pop()};
    interTermOperand oper {interTermOperand::plus};
    //bool isNeg {false};
    if (t.kind == TokenKind::minus)
        oper = interTermOperand::minus;
    else if (t.kind == TokenKind::plus)
        oper = interTermOperand::plus;
    else
        ts.push(t);

    serviceContainer& _sc {static_cast<serviceContainer&>(*this)};
    unique_ptr<abstractExpression> uptr = make_unique<generalTerm>(_sc);
    data.emplace_back(make_pair(oper, std::move(uptr)));

    while (true)
    {
        Token t {ts.pop()};
        switch(t.kind)
        {
            case TokenKind::plus:
            {
                oper = interTermOperand::plus;
                break;
            }
            case TokenKind::minus:
            {
                oper = interTermOperand::minus;
                break;
            }
            default:
            {
                ts.push(t);
                return;
            }
        }
        unique_ptr<abstractExpression> term = make_unique<generalTerm>(_sc);
        data.emplace_back(make_pair(oper, std::move(term)));
    }
}

compile_time_expression_structure::generalExpression::generalExpression(
        std::map<variableId, double>& _vars, Token_stream& _ts):
serviceContainer(_vars, _ts)
{
    initialize();
}

compile_time_expression_structure::generalExpression::generalExpression
(serviceContainer &sc):serviceContainer (sc)
{
    initialize();
}

double compile_time_expression_structure::generalExpression::value() const
{
    double result {0.0};
    for (const auto& ref : data)
    {
        auto& up {ref.second};
        if (up == nullptr)
            throw std::logic_error("null reference to abstractExpression in generalExpression::value");
        switch (ref.first)
        {
        case interTermOperand::plus:
            result += ref.second->value();
            break;
        case interTermOperand::minus:
            result -= ref.second->value();
            break;
        default:
            throw std::logic_error("undefined interTermOperand in generalExpression");
        }
    }
    return result;
}
