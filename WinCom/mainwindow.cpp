#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QLCDNumber>
#include <QMessageBox>
#include <QTextCursor>
#include <QMovie>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    movie = new QMovie(":/icon/resource/lihai.gif");
    ui->label_movie->setMovie(movie);
    movie->start();

    Init();
    ui->statusBar->showMessage(tr("WiCom准备就绪!"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Init status
void MainWindow::Init()
{
    myCom = NULL;
    //init button and action status
    setActionsEnabled(false);
    ui->write2fileButton->setEnabled(false);
    ui->closeMyComBtn->setEnabled(false);
    ui->sendMsgBtn->setEnabled(false);
    ui->sendMsglineEdit->setEnabled(false);
    ui->actionAddPort->setEnabled(true);

    findDialog = new SearchDialog(ui->textBrowser, this);

}

//set some action status
void MainWindow::setActionsEnabled(bool status)
{
    ui->actionSave->setEnabled(status);
    ui->actionClosePort->setEnabled(status);
    ui->actionCleanPort->setEnabled(status);
    ui->actionWriteToFile->setEnabled(status);
}

//Set ComboBox status
void MainWindow::setComboBoxEnabled(bool status)
{
    ui->portNameComboBox->setEnabled(status);
    ui->baudRateComboBox->setEnabled(status);
    ui->dataBitsComboBox->setEnabled(status);
    ui->parityComboBox->setEnabled(status);
    ui->stopBitsComboBox->setEnabled(status);
    ui->flowControlComboBox->setEnabled(status);
}

//Read serialport slot
void MainWindow::readMyCom()
{
    //Read all data of COM buffer to rcvData;
    rcvData = myCom->readAll();
    if(!rcvData.isEmpty())
    {
        if(write2fileName.isEmpty())
        {
            if(ui->ccradioButton->isChecked())
            {
                ui->textBrowser->insertPlainText(rcvData);
            }
            else if (ui->chradioButton->isChecked())
            {
                ui->textBrowser->append(tr(" ") + rcvData.toHex());
            }
        }
        else
        {
            //Write Data to file
            QFile file(write2fileName);
            if(!file.open(QFile::Append | QIODevice::Text))
            {
                QMessageBox::warning(this, tr("写入文件"), tr("打开文件 %1 失败, 无法写入\n%2")\
                                     .arg(write2fileName).arg(file.errorString()), QMessageBox::Ok);
                return;
            }

            QTextStream out(&file);
            out << rcvData << endl;
            file.close();
            ui->textBrowser->append(tr("数据已写入 %1").arg(write2fileName));
        }
    }

    //Show Bytes to LCD
    ui->recvbyteslcdNumber->display(ui->recvbyteslcdNumber->value() + rcvData.size());
    ui->statusBar->showMessage(tr("成功读取%1字节数据").arg(rcvData.size()));
}

//Open serialport slot
void MainWindow::on_openMyComBtn_clicked()
{

    //Get serialport name
    QString portname = ui->portNameComboBox->currentText();

    //Define serialport object, Specify the serialport's name and query mode.
    //myCom = new Win_QextSerialPort(portname, QextSerialBase::EventDriven);
    myCom = new QSerialPort();
    myCom->setPortName(portname);

    //Open serialport by R&W Mode
    if(!myCom->open(QIODevice::ReadWrite))
    {
        QMessageBox::critical(this, tr("串口打开失败"), tr("未能打开串口") + portname\
                              + tr("\n该设备不存在或已被占用"), QMessageBox::Ok);
        return;
    }

    baudrate_index = ui->baudRateComboBox->currentIndex();
    databits_index = ui->dataBitsComboBox->currentIndex();
    parity_index = ui->parityComboBox->currentIndex();
    stopbits_index = ui->stopBitsComboBox->currentIndex();
    flow_index = ui->flowControlComboBox->currentIndex();

    ComboboxToQt5Serialport serialportSetting(myCom, baudrate_index, databits_index,\
                                                    parity_index, stopbits_index, flow_index);
    //Set timeout
    //myCom->setTimeout(500);

    // Set pushbutton and actions status
    ui->openMyComBtn->setEnabled(false);
    ui->write2fileButton->setEnabled(true);
    ui->closeMyComBtn->setEnabled(true);
    ui->sendMsgBtn->setEnabled(true);

    ui->actionOpenPort->setEnabled(false);
    ui->actionAddPort->setEnabled(false);

    //Set Combox status
    setComboBoxEnabled(false);

    //set some actions status
    setActionsEnabled(true);

    //Associated signals and slots, when the serialport buffer has data, read the serialport.
    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));

    ui->statusBar->showMessage(tr("打开串口成功"));
}

//Switch write to file function
void MainWindow::on_write2fileButton_clicked()
{
    if(ui->write2fileButton->isChecked())
    {
        QString filename = QFileDialog::getSaveFileName(this, tr("写入文件"), 0, tr("保存为(*.*)"));
        if(filename.isEmpty())
        {
            ui->write2fileButton->setChecked(false);
        }
        else
        {
            write2fileName = filename;
            ui->textBrowser->setEnabled(false);
            ui->actionWriteToFile->setChecked(true);
            ui->actionWriteToFile->setText(tr("不写入."));
            ui->write2fileButton->setText(tr("不写入."));
        }
    }
    else
    {
        write2fileName.clear();
        ui->textBrowser->setEnabled(true);
        ui->actionWriteToFile->setChecked(false);
        ui->actionWriteToFile->setText(tr("写入.."));
        ui->write2fileButton->setText(tr("写入.."));
    }
}

//Close serialport slot
void MainWindow::on_closeMyComBtn_clicked()
{
    myCom->close();//close serialport
    delete myCom;
    myCom = NULL;


    //Set Combobox status
    setComboBoxEnabled(true);

    //set pushbutton and action status
    ui->openMyComBtn->setEnabled(true);
    ui->write2fileButton->setEnabled(false);
    ui->closeMyComBtn->setEnabled(false);
    ui->sendMsgBtn->setEnabled(false);
    ui->sendMsglineEdit->setEnabled(false);

    ui->actionOpenPort->setEnabled(true);
    ui->actionAddPort->setEnabled(true);

    //Set some actions status
    setActionsEnabled(false);

    ui->actionWriteToFile->setChecked(false);
    ui->statusBar->showMessage(tr("串口已经关闭"));
}

//Counter reset
void MainWindow::on_clearBytesBtn_clicked()
{
    if(ui->recvbyteslcdNumber->value())
    {
        ui->recvbyteslcdNumber->display(0);
        ui->statusBar->showMessage(tr("计数器已清零"));
    }
}

//Exit
void MainWindow::on_exitBtn_clicked()
{
    if((myCom != NULL))
    {
        if(myCom->isOpen())
        {
            myCom->close();
            delete myCom;
            myCom = NULL;
        }
    }

    this->close();
}

//Clear show
void MainWindow::on_clearShowBtn_clicked()
{
    ui->textBrowser->clear();
    ui->statusBar->showMessage(tr("记录已清空"));
}

//Send data
void MainWindow::on_sendMsgBtn_clicked()
{
    myCom->write(ui->sendMsglineEdit->text().toLatin1());
}

//Open serial by action
void MainWindow::on_actionOpenPort_triggered()
{
    on_openMyComBtn_clicked();
}

//Close serialport by action
void MainWindow::on_actionClosePort_triggered()
{
    on_closeMyComBtn_clicked();
}

//Clean I/O data
void MainWindow::on_actionCleanPort_triggered()
{
    myCom->flush();
}

//Counter reset by action
void MainWindow::on_actionClearBytes_triggered()
{
    on_clearBytesBtn_clicked();
}

//Exit by action
void MainWindow::on_actionExit_triggered()
{
    on_exitBtn_clicked();
}

//when textbrowser changed ,move cursor to end
void MainWindow::on_textBrowser_textChanged()
{
    ui->textBrowser->moveCursor(QTextCursor::End);
}

//Enable write data to file function
void MainWindow::on_actionWriteToFile_triggered()
{
    qDebug("%d\n", ui->actionWriteToFile->isChecked());
    if(ui->actionWriteToFile->isChecked())
    {
        QString filename = QFileDialog::getSaveFileName(this, tr("写入文件"), 0, tr("保存为(*.*)"));
        if(filename.isEmpty())
        {
            ui->actionWriteToFile->setChecked(false);//
        }
        else
        {
            write2fileName = filename;
            ui->textBrowser->setEnabled(false);
            ui->write2fileButton->setChecked(true);
            ui->actionWriteToFile->setText(tr("不写入."));
            ui->write2fileButton->setText(tr("不写入."));
        }
    }
    else
    {
        write2fileName.clear();
        ui->textBrowser->setEnabled(true);
        ui->write2fileButton->setChecked(false);
        ui->actionWriteToFile->setText(tr("写入.."));
        ui->write2fileButton->setText(tr("写入.."));
    }
}

//Call Find Dialog
void MainWindow::on_actionFind_triggered()
{
    findDialog->show();
}
//F3:Find next
void MainWindow::on_actionFindNext_triggered()
{
    findDialog->findNext();
}
//F4:Find previous
void MainWindow::on_actionFindPre_triggered()
{
    findDialog->findPrevious();
}

void MainWindow::on_actionSave_triggered()
{
    if(ui->textBrowser->toPlainText().isEmpty())
    {
        ui->statusBar->showMessage(tr("数据为空，无需保存"));
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this, tr("保存为"), tr("未命名.txt"));
    QFile file(filename);

    // if user cancel save, return null
    if(file.fileName().isEmpty())
    {
        return;
    }

    if(!file.open(QFile::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("保存文件"), tr("打开文件%1失败,无法保存\n%2").arg(filename).arg(file.errorString()), QMessageBox::Ok);
        return;
    }

    //write data to file
    QTextStream out(&file);
    out << ui->textBrowser->toPlainText();
    file.close();
    setWindowTitle("saved: " + QFileInfo(filename).canonicalFilePath());
}

void MainWindow::on_actionAbout_triggered()
{

}
