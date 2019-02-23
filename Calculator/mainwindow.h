#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <sstream>
#include <iostream>



#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void calculate(int a,int b);

private:
    Ui::MainWindow *ui;

private slots:
    void digit_pressed();
    void on_pushButton_equals_released();
    void on_pushButton_clear_released();
    void operator_pressed();
    void on_pushButton_hex_released();
    void on_pushButton_dec_released();
};




#endif // MAINWINDOW_H
