#include <cstdlib>
#include <sstream>
#include <iostream>
#include <queue>
#include "kernel.h"





int main(int argc, char *argv[])
{
    using namespace std;

#if 0

//    istringstream ist {"7*(2+4*(1+2*(3+6)))"};
//    istringstream ist {"7*(2+5)"};
    double real_expression_result = +7*(2+2*(1+3*(2+5))) - 30*3;
    istringstream ist {"+7*{2+2*(1+3*(2+5))} - 30*3"};
//    istringstream ist {"7*46 - 30*3"};
//    istringstream ist {"5*4 - 4*3"};
//    istringstream ist {"(-5)*4-4*3"};




    calculator::WExpression expr(ist);
    double val {expr.result()};
    cout << "res wcalc: " << val << endl;
    cout << "res   cpp: " << real_expression_result << endl;

    bool exit_instruction_received {false};
    while (cin)
    {
        cout << calculator::command_prompt_symbol << ' ';
        std::queue<string> queue_str;
        while (cin)
        {
            char sym {0};
            cin >> sym;
            while (cin && sym==calculator::command_stop_expression) cin >> sym;
            if (sym == calculator::command_quit_instruction) {
                exit_instruction_received = true;
                break;
            }
            else cin.unget();
            string str;
            while (cin)
            {
                cin >> sym;
                if (sym == calculator::command_stop_expression) break;
                str += sym;
            }
            queue_str.emplace(std::move(str));

//            istringstream ist{str};
//            try
//            {
//                calculator::WExpression expr(ist);
//                double val {expr.result()};
//                cout << " = " << val << endl;
//            }
//            catch(exception& e)
//            {
//                cout << " = " << "...failed - " << e.what() << endl;
//            }
        }

    }
#endif

    while (cin)
    {
        char sym {0};
        cin >> sym;
        while (cin && sym==calculator::command_stop_expression) cin >> sym;
        if (sym == calculator::command_quit_instruction) break;
        else cin.unget();
        string str;
        while (cin)
        {
            cin >> sym;
            if (sym == calculator::command_stop_expression) break;
            str += sym;
        }
        istringstream ist{str};
        try
        {
            std::map<std::string, double> vars {{"x", 3.1},
                                                {"y", 4.2},
                                                {"r", 6.3}};
            calculator::WExpression expr(ist, vars);
            double val {expr.result()};
            cout << " = " << val << endl;
        }
        catch(exception& e)
        {
            cout << " = " << "...failed - " << e.what() << endl;
        }
    }
    return EXIT_SUCCESS;
}
