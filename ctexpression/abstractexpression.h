#ifndef ABSTRACTEXPRESSION_H
#define ABSTRACTEXPRESSION_H
#include <map>
#include "ctexpressionrelatedunits.h"
//#include <stack>

namespace compile_time_expression_structure {

    class abstractExpression
    {

    public:
        abstractExpression()=default;
        virtual double value()const=0;
        virtual ~abstractExpression()=default;
    };


}

#endif // ABSTRACTEXPRESSION_H
