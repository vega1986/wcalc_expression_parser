#ifndef SERVICECONTAINER_H
#define SERVICECONTAINER_H
#include <map>
#include <string>
#include "ctexpressionrelatedunits.h"

namespace compile_time_expression_structure {



    class serviceContainer
    {
    protected:
        std::map<variableId, double>& vars; // outer variables
        Token_stream& ts; // outer token stream



    public:

        Token pop()
        {
            return ts.pop();
        }

        void push(Token t)
        {
            ts.push(t);
            return;
        }

        serviceContainer(std::map<variableId, double>& _vars, Token_stream& _ts)
            : vars(_vars), ts(_ts){}
        serviceContainer(serviceContainer& sc):vars(sc.vars), ts(sc.ts){}

    };

}

#endif // SERVICECONTAINER_H
