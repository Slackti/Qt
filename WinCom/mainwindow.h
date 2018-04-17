#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include "comboboxtoqt5serialport.h"
#include "searchdialog.h"

QT_BEGIN_NAMESPACE
class QSerialPort;
class QDialog;
class QString;
class QMovie;
QT_END_NAMESPACE

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
    void on_clearBytesBtn_clicked();
    void on_exitBtn_clicked();
    void on_clearShowBtn_clicked();//Clear buffer
    void on_sendMsgBtn_clicked();//Send data slot

    void on_actionOpenPort_triggered();//Open serialport
    void on_actionClosePort_triggered();
    void on_actionCleanPort_triggered();
    void on_actionClearBytes_triggered();
    void on_actionExit_triggered();

    void on_textBrowser_textChanged();
    void on_actionWriteToFile_triggered();//Switch write to file function by action
    void on_write2fileButton_clicked();//Switch write to file function by button
    void on_actionFind_triggered();
    void on_actionFindNext_triggered();
    void on_actionFindPre_triggered();
    void on_actionSave_triggered();
    void on_actionAbout_triggered();

private:
    QSerialPort *myCom;
    qint32 baudrate_index;
    qint32 databits_index;
    qint32 parity_index;
    qint32 stopbits_index;
    qint32 flow_index;

    QByteArray rcvData;
    QString write2fileName;
    QMovie *movie;
    SearchDialog *findDialog;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
