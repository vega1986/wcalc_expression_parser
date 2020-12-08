#ifndef PRIMARYNUMBER_H
#define PRIMARYNUMBER_H
#include <istream>
//#include "abstractexpression.h"
#include "generalprimary.h"

namespace compile_time_expression_structure {

    class primaryNumber final : public generalPrimary
    {
    private:
        const double v {0.0};
    public:
        primaryNumber(double _v):v(_v){}
        virtual double value()const;
        virtual ~primaryNumber()=default;
    };


}

#endif // PRIMARYNUMBER_H
