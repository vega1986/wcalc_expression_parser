# wcalc_expression_parser
expression calculator with functions, variables, constants

Отчет(Витушкин Денис):
список операторов: + - * / % !
cписок функций: pow cos sin tan acos asin atan atan2 exp log log10 sqrt abs
Результаты работы ф-й и операторов сравнивались с результатом работы ф-й библиотеки Numpy. Все ф-ии и операторы прошли тестирование(вопрос с %)
Сложные тесты:
1) (12+exp(5))*cos(tan(log(71)))-pow(sin(sqrt(tan(44))),acos(0.77)) --->успешно
        wcalc Res = -77.2799            numpy Res = -77.2799...
2) sqrt(12-log10(781)+abs(atan(2521)))*pow(21/5,tan(5))-172%17      ---->успешно
        wcalc Res = 3.01987             numpy Res = 3.01987...
3) exp(sin(cos(exp(abs(sqrt(log(log10(1487))))))))                  ---->успешно
        wcalc Res = 0.436475            numpy Res = 0.436475...
4) asin(acos(atan(cos(sin(0)))))                                    ----->успешно
        wcalc Res = 0                   numpy Res = 0.0
5) exp(sin(exp(10)/log10(5))-2+pow(17,abs(-0.1))) + 1.12613         ----->успешно
        wcalc Res = 2                   numpy Res = 1.9999978842742987
    Возникает вопрос, что будет, если к результату 5го теста применить mod2?
6)  (exp(sin(exp(10)/log10(5))-2+pow(17,abs(-0.1))) + 1.12613)%2    ------>провал
        wcalc Res = ошибка(left operand of %(mod) is not integer)
        ожидаемый Res = 0
        numpy Res = 1.999997884274298
7)  1.999999;0.999999;                                              ------>провал
        wcalc Res=  2                    numpy Res = 1.999999
                    0.999999                         0.999999
Так же во время тестирования столкнулся с проблемой обработки ошибок недопустимых аргументов у asin(acos) |x|>1  ,  log(log10)   x<0  ,  sqrt(x) x<0, при недопутимых значениях x результат работы: nan, что вводит в заблуждение при тестировании сложных функций(непонятно где ошибка), так что вместо nan выбрасывается исключение(bad argument for ...)

Предлагаю дополнить калькулятор функциями:
1) Функции библиотки cmath:
    -round
    -floor
    -ceil
    -trunc
2) Гиперболические функции:
    -sinh
    -cosh
    -tanh
    -asinh
    -acosh
    -atanh
3) Тригонометрические функции:
    -degrees(Преобразует радианную меру угла в градусную.)
    -radians(Преобразует градусную меру угла в радианную.)



                

