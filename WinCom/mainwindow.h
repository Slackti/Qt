#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "win_qextserialport.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void readMyCom();//Read serialport
    void on_openMyComBtn_clicked();//Open serialport
    void on_closeMyComBtn_clicked();//Close serialport
    void on_sendMsgBtn_clicked();//Send data slot

    void on_clearShowBtn_clicked();

private:
    Win_QextSerialPort *myCom;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
