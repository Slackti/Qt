#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    //init button and action status
    setActionsEnabled(false);
    ui->closeMyComBtn->setEnabled(false);
    ui->sendMsgBtn->setEnabled(false);
    ui->sendMsglineEdit->setEnabled(false);
    ui->actionAddPort->setEnabled(true);

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
}

//Read serialport slot
void MainWindow::readMyCom()
{
    //Read all data of COM buffer to temp;
    QByteArray temp = myCom->readAll();

    //if(!temp.isEmpty())
    //{

    //}

    //Show data to textbrowser
    ui->textBrowser->insertPlainText(temp);
}

//Open serialport slot
void MainWindow::on_openMyComBtn_clicked()
{

    //Get serialport name
    QString portname = ui->portNameComboBox->currentText();

    //Define serialport object, Specify the serialport's name and query mode.
    myCom = new Win_QextSerialPort(portname, QextSerialBase::EventDriven);

    //Open serialport by R&W Mode
    if(!myCom->open(QIODevice::ReadWrite))
    {
        QMessageBox::critical(this, tr("串口打开失败"), tr("未能打开串口") + portname\
                              + tr("\n该设备不存在或已被占用"), QMessageBox::Ok);
        return;
    }

    //Set baudRate
    myCom->setBaudRate((BaudRateType)ui->baudRateComboBox->currentIndex());

    //Set dataBits
    myCom->setDataBits((DataBitsType)ui->dataBitsComboBox->currentIndex());

    //Set parity
    myCom->setParity((ParityType)ui->parityComboBox->currentIndex());

    //Set stopBits
    myCom->setStopBits((StopBitsType)ui->stopBitsComboBox->currentIndex());

    //Set data FlowControl
    myCom->setFlowControl(FLOW_OFF);

    //Set timeout
    myCom->setTimeout(500);

    // Set pushbutton and actions status
    ui->openMyComBtn->setEnabled(false);
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

//Close serialport slot
void MainWindow::on_closeMyComBtn_clicked()
{
    myCom->close();//close serialport
    delete myCom;

    //Set Combobox status
    setComboBoxEnabled(true);

    //set pushbutton and action status
    ui->openMyComBtn->setEnabled(true);
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

//Send data slot
void MainWindow::on_sendMsgBtn_clicked()
{
    myCom->write(ui->sendMsglineEdit->text().toLatin1());
}

//Clear show by button
void MainWindow::on_clearShowBtn_clicked()
{
    ui->textBrowser->clear();
    ui->statusBar->showMessage(tr("记录已清空"));
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

//clean I/O data
void MainWindow::on_actionCleanPort_triggered()
{
    myCom->flush();
}

//counter reset
void MainWindow::on_actionClearBytes_triggered()
{
    if(ui->recvbyteslcdNumber->value())
    {
        ui->recvbyteslcdNumber->display(0);
        ui->statusBar->showMessage(tr("计数器已清零"));
    }
}

//Exit
void MainWindow::on_actionExit_triggered()
{
    if(myCom->isOpen())
    {
        myCom->close();
        delete myCom;
    }

    this->close();
}
