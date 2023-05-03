#include "calculator.h"
#include "ui_calculator.h"
#include "qmath.h"
#include "qregexp.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator), calcVal(0.0), mathOperator(0), sumInMemory(0.0)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString::number(calcVal));

    QPushButton *numButtons[10];

    for(int i = 0; i < 10; i++){
        numButtons[i] = Calculator::findChild<QPushButton *>("pushButton" + QString::number(i));

        connect(numButtons[i], SIGNAL(released()), this, SLOT(numPressed()));

    }

    connect(ui->pushButtonPlus, SIGNAL(released()), this, SLOT(mathOperatorPressed()));
    connect(ui->pushButtonMinus, SIGNAL(released()), this, SLOT(mathOperatorPressed()));
    connect(ui->pushButtonMul, SIGNAL(released()), this, SLOT(mathOperatorPressed()));
    connect(ui->pushButtonDiv, SIGNAL(released()), this, SLOT(mathOperatorPressed()));
    connect(ui->pushButtonPoten, SIGNAL(released()), this, SLOT(mathOperatorPressed()));

    connect(ui->pushButtonEq, SIGNAL(released()), this, SLOT(equalsPressed()));
    connect(ui->pushButtonSgn, SIGNAL(released()), this, SLOT(changeNumberSignPressed()));
    connect(ui->pushButtonDel, SIGNAL(released()), this, SLOT(deletePressed()));
    connect(ui->pushButtonClear, SIGNAL(released()), this, SLOT(clearScreenPressed()));
    connect(ui->pushButtonDot, SIGNAL(released()), this, SLOT(pointPressed()));


}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::numPressed(){
    QPushButton *pushButton = (QPushButton *)sender();

    QString buttonValue = pushButton->text();
    QString display = ui->lineEdit->text();

    if(display.toDouble() == 0 || display.toDouble() == 0.0){
        ui->lineEdit->setText(buttonValue);
    }else{
        QString newValue = display + buttonValue;
        double displayNewValue = newValue.toDouble();

        ui->lineEdit->setText((QString::number(displayNewValue)));
    }
}

void Calculator::mathOperatorPressed(){
    QString display = ui->lineEdit->text();

    calcVal = display.toDouble();

    QPushButton *pushButton = (QPushButton*)sender();
    QString buttonValue = pushButton->text();

    if(QString::compare(buttonValue, "/") == 0){
        mathOperator = 1;
    }else if(QString::compare(buttonValue, "*") == 0){
        mathOperator = 2;
    }else if(QString::compare(buttonValue, "+") == 0){
        mathOperator = 3;
    }else if(QString::compare(buttonValue, "^") == 0){
        mathOperator = 4;
    }else{
        mathOperator = 5;
    }

    ui->lineEdit->setText("");
}

void Calculator::equalsPressed(){
    double answer = 0.0;

    QString display =ui->lineEdit->text();

    double doubleDisplayValue = display.toDouble();

    switch(mathOperator){
        case 1:
            answer = calcVal / doubleDisplayValue;
        break;
        case 2:
            answer = calcVal * doubleDisplayValue;
        break;
        case 3:
            answer = calcVal + doubleDisplayValue;
        break;
        case 4:
            answer = qPow(calcVal, doubleDisplayValue);
        break;
        case 5:
            answer = calcVal - doubleDisplayValue;
        break;
        default:
            answer = 0.0;
        break;
    }

    ui->lineEdit->setText(QString::number(answer));
    sumInMemory = answer;
}

void Calculator::changeNumberSignPressed(){
    QString display = ui->lineEdit->text();
    QRegExp reg("[-]?[0-9]*");
    if(reg.exactMatch((display))){
        double doubleDisplay = display.toDouble();
        tr("-").toDouble();
        ui->lineEdit->setText(QString::number(doubleDisplay));
    }
}
void Calculator::clearScreenPressed(){
    ui->lineEdit->setText("0.0");
}
void Calculator::pointPressed(){
    QPushButton *pushButton = (QPushButton *)sender();

    QString buttonValue = pushButton->text();

    QString displayValue = ui->lineEdit->text();

    if(displayValue.toDouble() == 0 || displayValue.toDouble() == 0.0){
        ui->lineEdit->setText("Math error");
    }else{
        QString newValue = buttonValue + displayValue;

        double value = newValue.toDouble();
        if(!value){
            ui->lineEdit->setText("Math error");
        }else{
            ui->lineEdit->setText(QString::number(value));
        }
    }
}
void Calculator::deletePressed(){
    QString s = ui->lineEdit->text();
    ui->lineEdit->setText("");
    for(int i = 0; i < s.length()- 1; i++){

    }
}
