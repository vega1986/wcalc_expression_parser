#include <boost/math/constants/constants.hpp>
#include "servicecontainer.h"


double compile_time_expression_structure::serviceContainer::degrees(double rad)
{
    constexpr double pi = boost::math::constants::pi<double>();
    return rad * 180.0 / pi;
}

double compile_time_expression_structure::serviceContainer::radians(double deg)
{
    constexpr double pi = boost::math::constants::pi<double>();
    return deg * pi / 180.0;
}

// const std::map<compile_time_expression_structure::constantId, double>
// compile_time_expression_structure::serviceContainer::global_constants
// {
//     {constantId::pi, boost::math::constants::pi<double>()},
//     {constantId::e, boost::math::constants::e<double>()}
// };
// 
// const std::map<std::string, compile_time_expression_structure::constantId>
// compile_time_expression_structure::serviceContainer::global_constants_id
// {
//     {"pi", constantId::pi},
//     {"e", constantId::e}
// };
// 
// 
// const std::map<std::string, compile_time_expression_structure::variableId>
// compile_time_expression_structure::serviceContainer::global_variables_id
// {
//     {"x", variableId::x},
//     {"y", variableId::y},
//     {"r", variableId::r}
// };
