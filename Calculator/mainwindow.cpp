#include "mainwindow.h"
#include "ui_mainwindow.h"

int result;
bool isTyping = false;
bool isHex = false;
bool equals = false;
int op=0;
bool take=false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    /* we connected every button that is a digit with the slot digit_pressed()
    *  it gets activated with signal released()
    */
    connect(ui->pushButton_0, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_A, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_B, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_C, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_D, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_E, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_F, SIGNAL(released()),this,SLOT(digit_pressed()));

    // we connected every button that is an operator with the slot operator_pressed()
    // it gets activated with signal released()
    connect(ui->pushButton_add, SIGNAL(released()),this,SLOT(operator_pressed()));
    connect(ui->pushButton_multiply, SIGNAL(released()),this,SLOT(operator_pressed()));
    connect(ui->pushButton_subtract, SIGNAL(released()),this,SLOT(operator_pressed()));
    connect(ui->pushButton_divide, SIGNAL(released()),this,SLOT(operator_pressed()));

    // we set the buttons checkable to check later
    ui->pushButton_add->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_subtract->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_dec->setCheckable(true);
    ui->pushButton_hex->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * we use this function for displaying the digits that are pressed in an appropriate way
 * first we check if we are in mode hex, if any operator is checked and the user is not typing
 * the text on the button is displayed. Else if equals operator was called before pressing the button
 * it also displays the text on button. Else, it appends the text on button to the label's text and
 * displays the new string. If it is in dec mode, we do the similar things except we don't cast values
 * to integer. Also we don't append the new text if the current text is "0", we simply write the new
 * button text.
 */
void MainWindow::digit_pressed(){
    QPushButton* button = (QPushButton*)sender();
    int num;
    QString hexnum;
    if(!isHex){
        if(take&& !isTyping){
            num = button->text().toInt();
            isTyping = true;
            if(equals)
                equals=false;
        } else if (equals){
            num = button->text().toInt();
            equals=false;
        }
        else {
            num = (ui->label->text() + button->text()).toInt();
        }
        QString newnum;
        newnum = QString::number(num,'g',20);

        ui->label->setText(newnum);
    } else {
        if(take && !isTyping){
            hexnum = button->text();
            isTyping = true;
            if(equals)
                equals=false;
        }
        else {
            if(ui->label->text() == "0"){
                hexnum = button->text();
            }
            else {
                hexnum = (ui->label->text() + button->text());
            }
        }

        ui->label->setText(hexnum);

    }

}
void MainWindow::calculate(int second,int op){
     QString newnum;
    if(op==2){
        result+=second;
        if(isHex){
            uint decimal = result;
            QString hexadecimal;
            hexadecimal.setNum(decimal,16);
            newnum = hexadecimal.toUpper();
        }
        else
        {
            newnum = QString::number(result,'g',20);
        }
        ui->label->setText(newnum);

    }
    else if(op==3){
        result-=second;
        if(isHex){
            uint decimal = result;
            QString hexadecimal;
            hexadecimal.setNum(decimal,16);
            newnum = hexadecimal.toUpper();
        }
        else
        {
            newnum = QString::number(result,'g',20);
        }
        ui->label->setText(newnum);

    }
    else if(op==4){
        result*=second;
        if(isHex){
            uint decimal = result;
            QString hexadecimal;
            hexadecimal.setNum(decimal,16);
            newnum = hexadecimal.toUpper();
        }
        else
        {
            newnum = QString::number(result,'g',20);
        }
        ui->label->setText(newnum);

    }
    else if(op==5){
        if(second == 0){
                    newnum = "ERRORERRORERRORERROR";
                } else {
                    result/=second;
                    if(isHex){
                        uint decimal = result;
                        QString hexadecimal;
                        hexadecimal.setNum(decimal,16);
                        newnum = hexadecimal.toUpper();
                    }
                    else
                    {
                        newnum = QString::number(result,'g',20);
                    }
                }
                ui->label->setText(newnum);

    }
    isTyping = false;
    take=true;

}
/*
 * First we set equals to true. Then we check if the mode is hex. If it is, we assign
 * the label text to hexnum. We call the toUint function to convert hexnum to decimal
 * and store it in second. Else, we only store the text on label as integer.
 * We calculate the result by passing second and op as parameters. We assign zero to result
 * since the previous calculations is done. We assign zero to op so that it is not confused
 * with any other operator. We assign false to take so that it means no operator is checked
 * at the moment. It is used in digit_pressed().
*/
void MainWindow::on_pushButton_equals_released()
{
    equals = true;
    int second=0;

    QString hexnum;
    if(isHex){
        hexnum =ui->label->text();
        QString str = hexnum;
        bool ok;
        uint appId = str.toUInt(&ok,16);
        second = appId;

    } else {
        second = ui->label->text().toInt();
    }

    calculate(second,op);
    result=0;
    op=0;
    take=false;
}
// if clear is pressed it makes the label text "0"
void MainWindow::on_pushButton_clear_released()
{
    isTyping = false;
    ui->label->setText("0");

}

/*
 * If an operator is pressed first we declare two integer variables: op1 and first.
 * First is the first operand of any operator. or1 is the integer value for every operation
 * that is currently checked. We check if the calculator is in hex mode. If it is,
 * we convert the value on label to decimal and store it in first. Else we turn the
 * label text to integer and change the value of checked of the button to true.
 * op is the previous operation. If op equals 0, it means the calculator has just opened or
 * the previous operator was equals. We change op1 value according to the checked operator.
 * Then we change setChecked value of the pressed button to false. If equals is true, we assign false
 * to take, because take variable is used for any operator that was currently checked. It is used
 * for digit_pressed() method. Then we calculate the result by passing second and op as parameters
 * and op gets the value of op1.
 */
void MainWindow::operator_pressed(){
    int first=0;
    int op1=0;
    QPushButton* button = (QPushButton*)sender();
    QString hexnum;
    if(isHex){
        hexnum = ui->label->text();
        QString str = hexnum;
        bool ok;
        uint appId = str.toUInt(&ok,16);
        first = appId;
    } else {
        first = ui->label->text().toInt();
    }
    button->setChecked(true);
    if(op==0){
        result=first;
    }
    if(ui->pushButton_add->isChecked()){
        op1=2;
    }
    else if(ui->pushButton_subtract->isChecked()){
        op1=3;
    }
    else if(ui->pushButton_multiply->isChecked()){
        op1=4;
    }
    else if(ui->pushButton_divide->isChecked()){
        op1=5;
    }
    button->setChecked(false);
    if(equals)
        take=true;
    else
        take=false;
    calculate(first,op);
    op=op1;
}
/*
 * If hex button is pressed, if the calculator wasn't on the hex mode already, we
 * convert the current text on the label to hexadecimal and display it.
 * We also make isHex true.
 */
void MainWindow::on_pushButton_hex_released()
{
    QPushButton* button = (QPushButton*)sender();
    button->setChecked(true);
    ui->pushButton_dec->setChecked(false);
    if(!isHex){
        uint decimal = ui->label->text().toInt();
        QString hexadecimal;
        hexadecimal.setNum(decimal,16);
        ui->label->setText(hexadecimal.toUpper());
    }
    isHex = true;

}

/*
 * If dec button is pressed, if the calculator wasn't on the dec mode already, we
 * convert the current text on the label to decimal and display it.
 * We also make isHex false.
 */
void MainWindow::on_pushButton_dec_released()
{
    QPushButton* button = (QPushButton*)sender();
    button->setChecked(true);
    ui->pushButton_hex->setChecked(false);
    if(isHex){
        QString str = ui->label->text();
        bool ok;
        uint appId = str.toUInt(&ok,16);
        QString newnum = QString::number(appId,'g',20);
        ui->label->setText(newnum);
    }
    isHex = false;
}
