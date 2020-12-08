#ifndef GENERALTERM_H
#define GENERALTERM_H
#include <istream>
#include <vector>
#include <memory>
//#include "abstractexpression.h"
#include "generalprimary.h"
#include "servicecontainer.h"

namespace compile_time_expression_structure {

    class generalTerm final : public abstractExpression, private serviceContainer
    {
    private:
        std::vector<
                        std::pair<
                                    interPrimaryOperand,
                                    std::unique_ptr<generalPrimary>
                                 >
                   > data;
    public:
        generalTerm(serviceContainer&);
        virtual double value()const;
        virtual ~generalTerm()=default;

    };


}
#endif // GENERALTERM_H
