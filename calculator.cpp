
#include "calculator.h"
#include "ui_calculator.h"
#include "QHBoxLayout"
#include"QPushButton"
#include"QDebug"
#include"QtMath"
#include "QSignalSpy"
#include "QTest"
#include "QSettings"
#include <stack>
#include <cctype>

Calculator::Calculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calculator)
{

    ui->setupUi(this);
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::on_comma_clicked()
{
insertInput(".");
}
void Calculator::on_equals_clicked()
{
    QString input = ui->input->text();
    if(input.contains("++")||input.contains("--")||input.contains("^^")||input.contains("//")||input.contains("**"))
    { ui->result->setText("blad");}
   else{
    double result = parser.calculate(input.toStdString());
 ui->result->setText(QString::number(result,'f',15));//3 parametr precision
}
}
void Calculator::on_pi_clicked()
{
insertInput("3.141592653589793238");
}

void Calculator::on_opbracket_released()
{
    QString input = ui->input->text();//zeby wpisac otwarty nawias to trzeba miec znak przedtem a nie liczbe
    if (!input.isEmpty()){
        char last = input.back().toLatin1();
        if (isalnum(last) || last == ')')
            return;
    }
    insertInput("(");
}

void Calculator::on_closbracket_released()
{
    QString input = ui->input->text();//nie mozna wpisywac zamykajacego nawiasu jak otwartego jeszcze nie bylo
    int depth = 0;
    if (input.back() == '(' || isOperator(input.back()))
        return;
    for (QChar c : input){
        if (c == '(')
            ++depth;
        else if (c == ')')
            --depth;
    }
    if (depth > 0)
        insertInput(")");
}

void Calculator::on_cosh_released()
{
insertInput("cosh(");
}

void Calculator::on_tanh_released()
{
insertInput("tanh(");
}

void Calculator::on_ctgh_released()
{
insertInput("ctgh(");
}
void Calculator::on_element_clicked()
{
insertInput("sqrt(");
}

void Calculator::on_square_clicked()
{
insertInput("^2");
}

void Calculator::on_onebyx_clicked()
{
insertInput("1/");
}

void Calculator::on_C_clicked()
{
   ui->input->clear();
    ui->result->clear();
}
void Calculator::on_divide_clicked()
{
insertInput("/");
}

void Calculator::on_pushButton_7_clicked()
{
    insertInput("7");
}

void Calculator::on_pushButton_8_clicked()
{
    insertInput("8");
}

void Calculator::on_pushButton_9_clicked()
{
    insertInput("9");
}

void Calculator::on_multiply_clicked()
{
    insertInput("*");
}

void Calculator::on_pushButton_4_clicked()
{
    insertInput("4");
}

void Calculator::on_pushButton_5_clicked()
{
    insertInput("5");
}

void Calculator::on_pushButton_6_clicked()
{
    insertInput("6");
}

void Calculator::on_minus_clicked()
{
    insertInput("-");
}

void Calculator::on_pushButton_1_clicked()
{
    insertInput("1");
}

void Calculator::on_pushButton_2_clicked()
{
    insertInput("2");
}

void Calculator::on_pushButton_3_clicked()
{
    insertInput("3");
}

void Calculator::on_plus_clicked()
{
    insertInput("+");
}

void Calculator::on_pushButton_0_clicked()
{
    insertInput("0");
}
void Calculator::on_sin_clicked()
{
    insertInput("sin(");
}

void Calculator::on_cos_clicked()
{
    insertInput("cos(");
}

void Calculator::on_tan_clicked()
{
    insertInput("tan(");
}

void Calculator::on_ctg_clicked()
{
    insertInput("ctg(");
}

void Calculator::on_factorial_clicked()
{
        insertInput("!");
}

void Calculator::on_log_clicked()
{
    insertInput("log(");
}

void Calculator::insertInput(QString str)
{
    QString input=ui->input->text();
    if (input == "0"){
        ui->input->setText(str);
    }
    else{
        ui->input->setText(input + str);
    }
}

bool Calculator::isOperator(QChar ch)
{
    return ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^';
}

void Calculator::on_input_returnPressed()
{
    on_equals_clicked();
}

void Calculator::on_asinh_clicked()
{
    insertInput("asinh(");
}

void Calculator::on_acosh_clicked()
{
    insertInput("acosh(");
}

void Calculator::on_atanh_clicked()
{
    insertInput("tanh(");
}

void Calculator::on_abs_clicked()
{
    insertInput("abs(");
}

void Calculator::on_floor_clicked()
{
    insertInput("floor(");
}

void Calculator::on_ceil_clicked()
{
    insertInput("ceil(");
}

void Calculator::on_fabs_clicked()
{
    insertInput("fabs(");
}

void Calculator::on_sqrt_clicked()
{
    insertInput("sqrt(");
}

void Calculator::on_cbrt_clicked()
{
    insertInput("cbrt(");
}

void Calculator::on_log10_clicked()
{
    insertInput("log10(");
}

void Calculator::on_exp_clicked()
{
    insertInput("exp(");
}

void Calculator::on_acos_clicked()
{
    insertInput("acos(");
}

void Calculator::on_atan_clicked()
{
    insertInput("atan(");
}

void Calculator::on_asin_clicked()
{
    insertInput("asin(");
}

void Calculator::on_power_clicked()
{
    insertInput("^");
}
