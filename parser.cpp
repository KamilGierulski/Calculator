#include "parser.h"
#include"sstream"
#include"iomanip"
long long factorial(int val){
    long long res = 1;
    while (val > 1) {
        res *= val;
        --val;
    }
    return res;
}
void Parser::clear() {
    vals = {};
    ops = {};
    funcs = {};
}
double Parser::popVal() { // pop zdejmuje element ze szczytu stosu
    if (vals.empty())
        return numeric_limits<double>::quiet_NaN();//blad nan
    double val = vals.top();// top sluzy do odczytania lub modyfikacji wartosci umieszczonej na szczycie stosu
    vals.pop();
    return val;
}
double Parser::calculate(string s) {
        clear();
        powers.push(0); //zaczynamy z poziomem zagniezdzenia 0 ale na tym poziomie moga wystapic potegi, ktore poki co otworzyly 0 nawiasow
        double sign = 1;//do minusa
        for (size_t i = 0; i < s.size(); ++i) { //przeszukaj od lewej do prawej  size t to wlasciwie unsigned int likwidacja erroru implementacja algorytmu size to samo co length
            if (s[i] == ' ') {
                continue;
            }
            if (islower(s[i])) {//jesli jest funkcja to czytamy ja i do func wpisujemy np sin
                size_t k = i + 1;
                while (islower(s[k]))
                    ++k;
                size_t funcEnd = k;
                while (s[k] == ' ')
                    ++k;
                if (s[k] != '(')//funkcja musi zaczynac sie od nawiasu
                    return numeric_limits<double>::quiet_NaN();
                funcs.push(s.substr(i, funcEnd - i));
                i = k - 1;
            }
            else if (isdigit(s[i])) {//czytamy liczbe
                int num = 0;
                double dzies = 0.0;
                double mnoznik = 0.1;
                while (i<s.size() && isdigit(s[i]))
                {
                    num = num * 10 + (s[i++] - '0');
                }   //0 to 48 ASCII a 9 to 57 jakby prosta wersja atoi(string to int)
                if (s[i] == '.') { // jesli mamy liczbe po kropce to
                    ++i;
                    while ((i<s.size() && isdigit(s[i])))//jesli liczba jest typu 1.45
                    {
                        dzies += mnoznik*(s[i++] - '0');
                        mnoznik /= 10;
                    }
                }
                --i;
                double wyn = num + dzies;//dodajemy do siebie czesci
                vals.push(sign*wyn);
                sign = 1;
            }
            else if (s[i] == '(') {//if scanned  push
                ops.push(s[i]);
                powers.push(0); //wchodzimy na kolejny poziom zagniezdzenia na ktorym jeszcze nie ma poteg
            }
            else if (s[i] == ')') {
                //zamkniecie wszystkich nawiasow otorzonych przez potegi na aktualnym poziomie zagniezdzenia
                while (powers.top() > 0) {
                    if (ops.empty())
                        return numeric_limits<double>::quiet_NaN();
                    while (ops.top() != '(') {
                        double b = popVal();
                        if (!vals.empty()) {
                            char op = ops.top();
                            double a = popVal();
                            ops.pop();
                            vals.push(apply(a, b, op)*sign);
                            sign = 1;
                        }
                        else {
                            if (ops.top() == '(')
                                return b*sign;
                            else
                                return(b*-1);//liczby typu -(-5)
                        }
                    }
                    ops.pop();
                    if (!funcs.empty()) {
                        string func = funcs.top();
                        funcs.pop();
                        double res = applyFunc(func, vals.top());
                        vals.pop();
                        vals.push(res);
                    }
                    --powers.top(); //oznaczenie ze zamknelismy nawias
                }

                powers.pop(); //wychodzimy z poziomu zagniezdzenia

                if (ops.empty())
                    return numeric_limits<double>::quiet_NaN();
                while (ops.top() != '(') {
                    double b = popVal();
                    if (!vals.empty()) {
                        char op = ops.top();
                        double a = popVal();
                        ops.pop();
                        vals.push(apply(a, b, op)*sign);
                        sign = 1;
                    }
                    else {
                        if (ops.top() == '(')
                            return b*sign;
                        else
                            return(b*-1);//liczby typu -(-5)
                    }
                }
                ops.pop();
                if (!funcs.empty()) {
                    string func = funcs.top();
                    funcs.pop();
                    double res = applyFunc(func, vals.top());
                    vals.pop();
                    vals.push(res);
                }
            }
            else if (s[i] == '!') {
                double val = popVal();
                vals.push(double(factorial(int(val))));
            }
            else {
                if (s[i] == '-' && i == 0) {//przydatne do liczb typu --5
                    sign = -1;
                }
                else {
                    if (s[i] == '^') { //jesli potega to dodajemy operator i nawias czyli ^( bo operatory potegi maja byc odzwierciedlone w postaci a^(b^(c...))
                        ops.push(s[i]);
                        ops.push('(');
                        ++powers.top();
                    }
                    else {
                        //zamkniecie wszystkich nawiasow otorzonych przez potegi na aktualnym poziomie zagniezdzenia
                        while (powers.top() > 0) {
                            if (ops.empty())
                                return numeric_limits<double>::quiet_NaN();
                            while (ops.top() != '(') {
                                double b = popVal();
                                if (!vals.empty()) {
                                    char op = ops.top();
                                    double a = popVal();
                                    ops.pop();
                                    vals.push(apply(a, b, op)*sign);
                                    sign = 1;
                                }
                                else {
                                    if (ops.top() == '(')
                                        return b*sign;
                                    else
                                        return(b*-1);//liczby typu -(-5)
                                }
                            }
                            ops.pop();
                            if (!funcs.empty()) {
                                string func = funcs.top();
                                funcs.pop();
                                double res = applyFunc(func, vals.top());
                                vals.pop();
                                vals.push(res);
                            }
                            --powers.top();//oznaczenie ze zamknelismy nawias
                        }

                        while (!ops.empty() && ops.top() != '(' && precedence(s[i]) <= precedence(ops.top())) {//tylko tu uzywamy priorytetu
                            double b = vals.top();
                            vals.pop();
                            double a = vals.top();
                            vals.pop();
                            char op = ops.top();
                            ops.pop();
                            vals.push(apply(a, b, op)*sign);
                            sign = 1;
                        }

                        ops.push(s[i]);
                    }
                }
            }
        }
        //zamkniecie wszystkich nawiasow otorzonych przez potegi na aktualnym poziomie zagniezdzenia
        while (powers.top() > 0) {
            if (ops.empty())
                return numeric_limits<double>::quiet_NaN();
            while (ops.top() != '(') {
                double b = popVal();
                if (!vals.empty()) {
                    char op = ops.top();
                    double a = popVal();
                    ops.pop();
                    vals.push(apply(a, b, op)*sign);
                    sign = 1;
                }
                else {
                    if (ops.top() == '(')
                        return b*sign;
                    else
                        return(b*-1);//liczby typu -(-5)
                }
            }
            ops.pop();
            if (!funcs.empty()) {
                string func = funcs.top();
                funcs.pop();
                double res = applyFunc(func, vals.top());
                vals.pop();
                vals.push(res);
            }
            --powers.top();//oznaczenie ze zamknelismy nawias
        }

        while (!ops.empty()) {
            double b = popVal();
            if (!ops.empty()) {
                char op = ops.top();
                ops.pop();
                double a = popVal();
                vals.push(apply(a, b, op)*sign);
                sign = 1;
            }
            else {
                if (vals.empty())
                    return b*sign;
                else
                    return numeric_limits<double>::quiet_NaN();
            }
        }
        return vals.top();
    }
double Parser::apply(double a, double b, char op) {
    if (op == '+')
        return a + b;
    else if (op == '-')
        return a - b;
    else if (op == '*')
        return a * b;
    else if (op == '/')
        return a / b;
    else if (op == '^')
        return pow(a, b);
    else
        return numeric_limits<double>::quiet_NaN();
}
int Parser::precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '^')
        return 3;
    else
        return 3;
}
double Parser::applyFunc(string func, double val) {
    if (func == "sin") {
        return sin(val);
    }
    else if (func == "cos") {
        return cos(val);
    }
    else if (func == "tan"){
        return tan(val);
    }
    else if (func == "acosh") {
        return acosh(val);
    }
    else if (func == "asinh") {
        return asinh(val);
    }
    else if (func == "cosh") {
        return cosh(val);
    }
    else if (func == "atan") {
        return atan(val);
    }
    else if (func == "sinh") {
        return sinh(val);
    }
    else if (func == "tanh") {
        return tanh(val);
    }
    else if (func == "atanh"){
        return atanh(val);
    }
    else if (func == "asin"){
    return asin(val);
    }
    else if (func == "acos"){
    return acos(val);
    }
    else if (func == "exp"){
    return exp(val);
    }
    else if (func == "log"){
    return log(val);
    }
    else if (func == "log10"){
    return log10(val);
    }
    else if (func == "cbrt"){
    return cbrt(val);
    }
    else if (func == "sqrt"){
    return sqrt(val);
    }
    else if (func == "ceil"){
    return ceil(val);
    }
    else if (func == "floor"){
    return floor(val);
    }
    else if (func == "fabs"){
    return fabs(val);
    }
    else if (func == "abs"){
    return abs(val);
    }


    else {
        return numeric_limits<double>::quiet_NaN();
    }
}
