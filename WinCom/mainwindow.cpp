#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->closeMyComBtn->setEnabled(false);
    ui->sendMsgBtn->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Read serialport slot
void MainWindow::readMyCom()
{
    //Read all data of COM buffer to temp;
    QByteArray temp = myCom->readAll();
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
    myCom->open(QIODevice::ReadWrite);

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

    //Associated signals and slots, when the serialport buffer has data, read the serialport.
    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));

    // Set pushbutton status
    ui->openMyComBtn->setEnabled(false);
    ui->closeMyComBtn->setEnabled(true);
    ui->sendMsgBtn->setEnabled(true);

    //Set Combox status
    ui->portNameComboBox->setEditable(false);
    ui->baudRateComboBox->setEditable(false);
    ui->dataBitsComboBox->setEnabled(false);
    ui->parityComboBox->setEnabled(false);
    ui->stopBitsComboBox->setEnabled(false);


}

//Close serialport slot
void MainWindow::on_closeMyComBtn_clicked()
{
    myCom->close();//close serialport

    //set pushbutton status
    ui->openMyComBtn->setEnabled(true);
    ui->closeMyComBtn->setEnabled(false);
    ui->sendMsgBtn->setEnabled(false);

    //Set Combox status
    ui->portNameComboBox->setEditable(true);
    ui->baudRateComboBox->setEditable(true);
    ui->dataBitsComboBox->setEnabled(true);
    ui->parityComboBox->setEnabled(true);
    ui->stopBitsComboBox->setEnabled(true);
}

//Send data slot
void MainWindow::on_sendMsgBtn_clicked()
{
    myCom->write(ui->sendMsglineEdit->text().toLatin1());
}

void MainWindow::on_clearShowBtn_clicked()
{
    ui->textBrowser->clear();
}
