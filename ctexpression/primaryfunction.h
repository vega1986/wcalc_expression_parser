#ifndef PRIMARYFUNCTION_H
#define PRIMARYFUNCTION_H
#include <vector>
#include <memory>
//#include "abstractexpression.h"
#include "generalprimary.h"
#include "servicecontainer.h"

namespace compile_time_expression_structure {

    class primaryFunction final : public generalPrimary, private serviceContainer
    {
    private:
        std::vector<std::unique_ptr<abstractExpression> > args;
        functionId id;
    public:
        primaryFunction(functionId _id, serviceContainer& sc);
        virtual double value()const;
        virtual ~primaryFunction()=default;
    };

}

#endif // PRIMARYFUNCTION_H
