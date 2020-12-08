#ifndef PRIMARYEXPRESSION_H
#define PRIMARYEXPRESSION_H
#include <memory>
#include "generalprimary.h"

namespace compile_time_expression_structure {

    class primaryExpression final : public generalPrimary, private serviceContainer
    {
    private:
        std::unique_ptr<abstractExpression> expr;
    public:
        primaryExpression(serviceContainer& sc);
        virtual double value()const;
        virtual ~primaryExpression()=default;

    };

}

#endif // PRIMARYEXPRESSION_H
