#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <hemm.cpp>
#include <algorithm>
#include <bitset>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString text_to_code = ui->lineEdit->text();

    text_to_code.replace(QString("1"), QString(""));
    text_to_code.replace(QString("0"), QString(""));


    if ( text_to_code.length() )
    {
        ui->lineEdit->clear();
        ui->textBrowser->setText("error");
        return ;
    }

    text_to_code = ui->lineEdit->text();

    QString coded = "";
    coded.append( code(text_to_code.toLatin1().data() ) );

    ui->textBrowser->setText( coded);
}

void MainWindow::on_lineEdit_3_returnPressed()
{
    int error = decode(ui->lineEdit_3->text().toLocal8Bit().data());

    ui->lcdNumber->display(error);

    QString result = ui->lineEdit_3->text();

    if ( error )
    {
        if ( result.data()[error-1] == '0')
        {
            result.data()[error-1] = '1';
        }else{
            result.data()[error-1] = '0';
        }
    }
    ui->textBrowser_2->setText("Result : ");

    ui->textBrowser_2->append(result);

    ui->textBrowser_2->append("Original : ");
    QString original = decode_to_original(ui->lineEdit_3->text().toLocal8Bit().data());

    ui->textBrowser_2->append(original);

    int ch = 0;
    for ( int i = 0; i < original.length(); ++i)
    {
        if ( original.data()[7-i-1] == '1')
        {
            int two = 1;
            for ( int k = 1; k <= i; ++k)
            {
                two *= 2;
            }
            ch += two;
        }
    }

    QString c(ch);

    ui->textBrowser_2->append("Char : ");
    ui->textBrowser_2->append(c);
}

template<typename T>
std::string get_bits(T value) {
    int size = sizeof(value) * CHAR_BIT;
    std::string ret;
    ret.reserve(size);
    for (int i = size-1; i >= 0; --i)
        ret += (value & (1 << i)) == 0 ? '0' : '1';
    return ret;
}

void MainWindow::on_lineEdit_2_returnPressed()
{
    QString ch = ui->lineEdit_2->text();

    if ( ch.length() != 1)
    {
        ui->lineEdit_2->clear();
        ui->textBrowser->setText("error");
        return ;
    }


    std::string numm = get_bits(ch.toLatin1().data()[0]);

    QString num(numm.data());

    std::reverse(num.begin(), num.end());

    char* temp  = new char[8];
    for ( int i = 0; i < 8; ++i)
    {
        temp[i] = num.toLatin1().data()[i];
    }


    temp[7] = '\0';
    num = QString(temp);

    std::reverse(num.begin(), num.end());

    QString codded = code(num.toLatin1().data());

    ui->textBrowser->setText(codded);
}
