#ifndef GENERALEXPRESSION_H
#define GENERALEXPRESSION_H
#include <istream>
#include <vector>
#include <memory>
#include "abstractexpression.h"
#include "servicecontainer.h"

namespace compile_time_expression_structure {

    class generalExpression final : public abstractExpression, private serviceContainer
    {
    private:


        std::vector<
                    std::pair<
                                interTermOperand,
                                std::unique_ptr<abstractExpression>
                             >
                   > data;

        inline void initialize();

    public:
        generalExpression(std::map<variableId, double>& _vars, Token_stream& _ts);
        generalExpression(serviceContainer& sc);
        virtual double value()const;
        virtual ~generalExpression()=default;
    };


}

#endif // GENERALEXPRESSION_H
