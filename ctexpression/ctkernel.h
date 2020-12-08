#ifndef KERNEL_H
#define KERNEL_H
#include <istream>
#include <stack>
#include <map>

#include "generalexpression.h"

namespace compile_time_expression_structure {



    class CTExpression {
    private:
        Token_stream ts;
        std::map<variableId, double> variables;


        generalExpression ge;

    public:
        CTExpression(std::istream& ist):
        ts(ist), ge(variables, ts)
        {}
        void set_variable(variableId id, double value)
        {
            variables[id] = value;
            return;
        }
        double value()
        {
            return ge.value();
        }

    };
}

#endif // KERNEL_H
