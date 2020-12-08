#ifndef PRIMARYVARIABLE_H
#define PRIMARYVARIABLE_H
//#include "abstractexpression.h"
#include "generalprimary.h"
#include "servicecontainer.h"

namespace compile_time_expression_structure {

    class primaryVariable final : public generalPrimary, private serviceContainer
    {
    private:
//        const double& ref;
        variableId id {variableId::undef};
    public:
        primaryVariable(variableId _id, serviceContainer& sc):serviceContainer(sc),id(_id){}
        virtual double value()const;
        virtual ~primaryVariable()=default;

    };

}

#endif // PRIMARYVARIABLE_H
