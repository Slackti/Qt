#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "win_qextserialport.h"
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Init();

protected:
    void setActionsEnabled(bool status);
    void setComboBoxEnabled(bool status);

private slots:
    void readMyCom();//Read serialport
    void on_openMyComBtn_clicked();//Open serialport
    void on_closeMyComBtn_clicked();//Close serialport
    void on_sendMsgBtn_clicked();//Send data slot
    void on_clearShowBtn_clicked();//Clear buffer

    void on_actionOpenPort_triggered();//Open serialport
    void on_actionClosePort_triggered();
    void on_actionCleanPort_triggered();

    void on_actionClearBytes_triggered();

    void on_actionExit_triggered();

private:
    Win_QextSerialPort *myCom;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
