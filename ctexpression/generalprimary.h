#ifndef GENERALPRIMARY_H
#define GENERALPRIMARY_H
#include <memory>
#include "abstractexpression.h"
#include "servicecontainer.h"

namespace compile_time_expression_structure {


    class generalPrimary : public abstractExpression
    {
    private:
        bool isFactorial {false};
    public:
        generalPrimary()=default;
        void setFactorial(bool _isFactorial)
        {
            isFactorial = _isFactorial;
            return;
        }
        virtual double value()const=0; // still abstract class
        double value(double prime)const;
        virtual ~generalPrimary()=default;
        static std::unique_ptr<generalPrimary> createPrimary(serviceContainer& sc);
//        static std::unique_ptr<generalPrimary> createFunction(std::string fname, serviceContainer& sc);
    };
}
#endif // GENERALPRIMARY_H
