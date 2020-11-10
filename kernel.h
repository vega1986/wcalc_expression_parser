#ifndef KERNEL_H
#define KERNEL_H
#include <istream>
#include <stack>
#include <map>
#include <boost/math/constants/constants.hpp>

namespace calculator {

    static constexpr char command_stop_expression {';'};
    static constexpr char command_quit_instruction {'q'};
    static constexpr char command_prompt_symbol {'>'};


    enum class TokenKind : std::uint8_t {
                                     bracket_left0  =  0,
                                     bracket_right0 =  1,
                                     bracket_left1  =  2,
                                     bracket_right1 =  3,
                                     multiply       =  4,
                                     divide         =  5,
                                     mod            =  6,
                                     plus           =  7,
                                     minus          =  8,
                                     number         =  9,
                                     factorial      = 10,
                                     variable       = 11,
                                     function       = 12,
                                     comma          = 13,
                                     undef          = 14};
    struct Token {
        TokenKind kind {TokenKind::undef};
        double value {0.0};
        std::string name {""};
        Token(TokenKind _kind=TokenKind::undef, double _value=0.0, std::string _name=""):kind(_kind),value(_value),name(_name){}
//        Token(TokenKind _kind=TokenKind::undef, std::string _name=""):kind(_kind),value(0.0),name(_name){}
    };

//    using Token_stream = std::stack<Token>;

    class Token_stream {
    private:
        std::istream& ist;
        std::stack<Token> data;

    public:
        Token_stream(std::istream& _ist): ist(_ist){}
        Token pop();
        void push(Token t)
        {
            data.push(t);
        }
        bool empty(){
            return data.empty();
        }


    };

    class WExpression {
    public:
        WExpression(std::istream& _ist, std::map<std::string, double> _variables): ist(_ist), ts(_ist), variables(_variables){}
    private:
        std::istream& ist;
        Token_stream ts;
        std::map<std::string, double> variables;
        static const std::map<std::string, double> global_constants;
//        {
//            {"e", boost::math::constants::pi<double>()},
//            {"pi", boost::math::constants::e<double>()}
//        };
//        Token get_token(std::istream& ist);
        double expression();
        double term();
        double primary();
        double function(std::string);
    public:
        double result()
        {
            return expression();
        }

    };
}

#endif // KERNEL_H
