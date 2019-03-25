#ifndef PARSER_H
#define PARSER_H
#include <string>
#include<iostream>
#include <stack>
#include<vector>
#include <cmath>
#include <limits>
/*
Algorithm infix to postfix
1. Scan the infix expression from left to right.
2. If the scanned character is an operand, output it.
3. Else,
…..3.1 If the precedence of the scanned operator is greater than the precedence of the operator in the stack(or the stack is empty or the stack contains a ‘(‘ ), push it.
…..3.2 Else, Pop all the operators from the stack which are greater than or equal to in precedence than that of the scanned operator. After doing that Push the scanned operator to the stack. (If you encounter parenthesis while popping then stop there and push the scanned operator in the stack.)
4. If the scanned character is an ‘(‘, push it to the stack.
5. If the scanned character is an ‘)’, pop the stack and and output it until a ‘(‘ is encountered, and discard both the parenthesis.
6. Repeat steps 2-6 until infix expression is scanned.
7. Print the output
8. Pop and output from the stack until it is not empty.
*/
using namespace std; //infix expression to postfix expression so that we can evaluate the expression using a stack very easily
long long factorial(int val);//silnia
class Parser {
    stack<double> vals;
    stack<char> ops;
    stack<string> funcs;
    stack<int> powers; //stos ktory zawiera ilosci nawiasow otwartych przez operatory ktore maja byc wykonywane od prawej do lewej (tutaj potega). wartosc na szczycie stosu odpowiada aktualnemu poziomowi zagniezdzenia w nawiasach
    //przyklad: napotykamy ^ to otwieramy nawias ^(, zliczamy ilosc otwartych w ten sposob nawiasow w wartosci na szczycie stosu powers
    //nawiasy te pozniej zamykamy kiedy napotykamy inny operator albo nawias zamykajacy ) w wyrazeniu albo koniec wyrazenia
    void clear();//czysci
double popVal();//pop ze stosu
public:
double calculate(string s);//glowna funkcja w programie
private:
    double apply(double a, double b, char op);//+-*/^
    int precedence(char op);//priorytet operatorow
    double applyFunc(string func, double val);//funkcje wbudowane
};
#endif // PARSER_H
