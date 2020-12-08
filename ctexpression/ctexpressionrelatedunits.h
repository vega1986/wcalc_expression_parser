#ifndef CTEXPRESSIONRELATEDUNITS_H
#define CTEXPRESSIONRELATEDUNITS_H
#include <boost/math/constants/constants.hpp>
#include <string>
#include <stack>
#include <istream>
#include <map>

namespace compile_time_expression_structure {
    static constexpr char command_stop_expression {';'};
    static constexpr char command_quit_instruction {'q'};
    static constexpr char command_prompt_symbol {'>'};



    enum class TokenKind : unsigned short {
                                     bracket_left0  =  0,
                                     bracket_right0 =  1,
                                     multiply       =  2,
                                     divide         =  3,
                                     mod            =  4,
                                     plus           =  5,
                                     minus          =  6,
                                     number         =  7,
                                     factorial      =  8,
                                     variable       =  9,
                                     function       = 10,
                                     comma          = 11,
                                     undef          = 12};

    enum class interTermOperand : unsigned short {
        undef = 0, // unknown
         plus = 1,
        minus = 2};

    enum class interPrimaryOperand : unsigned short {
           undef = 0,
        multiply = 1,
          divide = 2,
             mod = 3
    };

    enum class variableId : unsigned short {
        undef = 0,
        x = 1,
        y = 2,
        r = 3
    };

    enum class constantId : unsigned short {
        undef = 0,
        pi = 1,
        e = 2

    };

    enum class functionId : unsigned int {
        undef = 0,
        pow = 1,
        cos = 2,
        sin = 3,
        tan = 4,
        acos = 5,
        asin = 6,
        atan = 7,
        atan2 = 8,
        exp = 9,
        log = 10,
        log10 = 11,
        sqrt = 12,
        abs = 13,
        
        // new function recomended by Denis
        
        round = 14,
        floor = 15,
        ceil = 16,
        trunc = 17,
        
        sinh = 18,
        cosh = 19,
        tanh = 20,
        asinh = 21,
        acosh = 22,
        atanh = 23,
        
        degrees = 24,
        radians = 25
        
    };


    const std::map<std::string, functionId> global_functions_id {
        {    "pow", functionId::pow  },
        {    "cos", functionId::cos  },
        {    "sin", functionId::sin  },
        {    "tan", functionId::tan  },
        {   "acos", functionId::acos },
        {   "asin", functionId::asin },
        {   "atan", functionId::atan },
        {  "atan2", functionId::atan2},
        {    "exp", functionId::exp  },
        {    "log", functionId::log  },
        {  "log10", functionId::log10},
        {   "sqrt", functionId::sqrt },
        {    "abs", functionId::abs  },
        
        {  "round", functionId::round},
        {  "floor", functionId::floor},
        {   "ceil", functionId::ceil},
        {  "trunc", functionId::trunc},
        
        {   "sinh", functionId::sinh},
        {   "cosh", functionId::cosh},
        {   "tanh", functionId::tanh},
        {  "asinh", functionId::asinh},
        {  "acosh", functionId::acosh},
        {  "atanh", functionId::atanh},
        {"degrees", functionId::degrees},
        {"radians", functionId::radians}
        
    };

    const std::map<constantId, double> global_constants {
        {constantId::pi, boost::math::constants::pi<double>()},
        {constantId::e, boost::math::constants::e<double>()}
    };
    const std::map<std::string, constantId> global_constants_id
    {
        {"pi", constantId::pi},
        {"e", constantId::e}
    };
    const std::map<std::string, variableId> global_variables_id
    {
        {"x", variableId::x},
        {"y", variableId::y},
        {"r", variableId::r}
    };


    struct Token {
        TokenKind kind {TokenKind::undef};
        double value {0.0};
        std::string name {""};
        Token(  TokenKind  _kind = TokenKind::undef,
                   double _value = 0.0,
              std::string  _name = "")
            :
            kind(_kind),
            value(_value),
            name(_name){}
    };

    class Token_stream {
    private:
        std::stack<Token> data;
        std::istream& ist;
    public:
        Token_stream(std::istream& _ist):ist(_ist){}
        Token pop()
        {
            if (!(data.empty()))
            {
                auto res = data.top();
                data.pop();
                return res;
            }
            Token result;
            if (!ist) return result;
            char sym {0};
            ist >> sym;
            if (ist.eof()) return result;
            switch (sym)
            {
                case '(':
                    result.kind = TokenKind::bracket_left0;
                    break;
                case ')':
                    result.kind = TokenKind::bracket_right0;
                    break;
                case '*':
                    result.kind = TokenKind::multiply;
                    break;
                case '/':
                    result.kind = TokenKind::divide;
                    break;
                case '%':
                    result.kind = TokenKind::mod;
                    break;
                case '+':
                    result.kind = TokenKind::plus;
                    break;
                case '-':
                    result.kind = TokenKind::minus;
                    break;
                case '!':
                    result.kind = TokenKind::factorial;
                    break;
                case ',':
                    result.kind = TokenKind::comma;
                    break;
                case '.':
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                {
                    ist.unget();
                    double val {0.0};
                    ist >> val;
                    result.kind = TokenKind::number;
                    result.value = val;
                    break;
                }
                default:
                {
                    if (isalpha(sym)) // function or variable or constant name
                    {
                        std::string s;
                        s += sym;
                        char ch {0};
                        while (ist.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
                        ist.putback(ch);
                        ist >> ch;
                        if (ch == '(')
                        {
                            ist.putback(ch);
                            result.kind = TokenKind::function;
                            result.name = s;
                            break;
                        }
                        else
                        {
                            ist.putback(ch);
                            result.kind = TokenKind::variable;
                            result.name = s;
                            break;
                        }
                    }
                    else
                    {
                        throw std::logic_error("bad Token");
                    }
                }
            }
            return result;
        }
        void push(Token t)
        {
            data.push(t);
        }
        bool empty(){
            return data.empty();
        }
        void clear()
        {
            while (!(data.empty()))
                data.pop();
            return;
        }


    };





}

#endif // CTEXPRESSIONRELATEDUNITS_H
