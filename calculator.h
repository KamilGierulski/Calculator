#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include "parser.h"

namespace Ui {
class Calculator;
}

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent=0);
    ~Calculator();
    double firstNum;
    bool userIsTypingSecondNumber=false;
public slots:
  void on_comma_clicked();
  void on_C_clicked();
  void on_equals_clicked();
  void on_pi_clicked();

private slots:
  void on_opbracket_released();
  void on_closbracket_released();

  void on_cosh_released();

  void on_tanh_released();

  void on_ctgh_released();

  void on_element_clicked();

  void on_square_clicked();

  void on_onebyx_clicked();


  void on_divide_clicked();

  void on_pushButton_7_clicked();

  void on_pushButton_8_clicked();

  void on_pushButton_9_clicked();

  void on_multiply_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_5_clicked();

  void on_pushButton_6_clicked();

  void on_minus_clicked();

  void on_pushButton_1_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

  void on_plus_clicked();

  void on_pushButton_0_clicked();
  void on_sin_clicked();

  void on_cos_clicked();

  void on_tan_clicked();

  void on_ctg_clicked();

  void on_factorial_clicked();

  void on_log_clicked();

  void on_input_returnPressed();

  void on_asinh_clicked();

  void on_acosh_clicked();

  void on_atanh_clicked();

  void on_abs_clicked();

  void on_floor_clicked();

  void on_ceil_clicked();

  void on_fabs_clicked();

  void on_sqrt_clicked();

  void on_cbrt_clicked();

  void on_log10_clicked();

  void on_exp_clicked();

  void on_acos_clicked();

  void on_atan_clicked();

  void on_asin_clicked();

  void on_power_clicked();

private:
    Parser parser;
    Ui::Calculator *ui;
    void insertInput(QString str);
    bool isOperator(QChar ch);
};

#endif // CALCULATOR_H
