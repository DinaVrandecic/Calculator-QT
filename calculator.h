#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void numPressed();
    void mathOperatorPressed();
    void equalsPressed();
    void changeNumberSignPressed();
    void clearScreenPressed();
    void pointPressed();
    void deletePressed();

private:
    Ui::Calculator *ui;
    double calcVal;
    int mathOperator;
    double sumInMemory;
};
#endif // CALCULATOR_H
