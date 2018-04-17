#ifndef COMBOBOXTOQT5SERIALPORT_H
#define COMBOBOXTOQT5SERIALPORT_H

#include <QMainWindow>

#include <QtSerialPort/QSerialPort>

class ComboboxToQt5Serialport
{
public:
    ComboboxToQt5Serialport();
    ComboboxToQt5Serialport(QSerialPort *myCom, qint32 baudrate_index, qint32 databits_index, \
                            qint32 parity_index, qint32 stopbits_index, qint32 flow_index)
    {
        //Set baudrate
        switch (baudrate_index) {
        case 0:
            myCom->setBaudRate(QSerialPort::Baud1200,QSerialPort::AllDirections);
            break;
        case 1:
            myCom->setBaudRate(QSerialPort::Baud2400,QSerialPort::AllDirections);
            break;
        case 2:
            myCom->setBaudRate(QSerialPort::Baud4800,QSerialPort::AllDirections);
            break;
        case 3:
            myCom->setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections);
            break;
        case 4:
            myCom->setBaudRate(QSerialPort::Baud19200,QSerialPort::AllDirections);
            break;
        case 5:
            myCom->setBaudRate(QSerialPort::Baud38400,QSerialPort::AllDirections);
            break;
        case 6:
            myCom->setBaudRate(QSerialPort::Baud57600,QSerialPort::AllDirections);
            break;
        case 7:
            myCom->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);
            break;
        default:
            myCom->setBaudRate(QSerialPort::UnknownBaud,QSerialPort::AllDirections);
            break;
        }

        //Set data bit
        switch (databits_index) {
        case 0:
            myCom->setDataBits(QSerialPort::Data5);
            break;
        case 1:
            myCom->setDataBits(QSerialPort::Data6);
            break;
        case 2:
            myCom->setDataBits(QSerialPort::Data7);
            break;
        case 3:
            myCom->setDataBits(QSerialPort::Data8);
            break;
        default:
            myCom->setDataBits(QSerialPort::UnknownDataBits);
            break;
        }

        //Set parity
        switch (parity_index) {
        case 0:
            myCom->setParity(QSerialPort::NoParity);
            break;
        case 1:
            myCom->setParity(QSerialPort::OddParity);
            break;
        case 2:
            myCom->setParity(QSerialPort::EvenParity);
            break;
        default:
            myCom->setParity(QSerialPort::UnknownParity);
            break;
        }

        //Set Stop bit
        switch (stopbits_index) {
        case 0:
            myCom->setStopBits(QSerialPort::OneStop);
            break;
        case 1:
            myCom->setStopBits(QSerialPort::TwoStop);
            break;
        default:
            myCom->setStopBits(QSerialPort::UnknownStopBits);
            break;
        }

        switch(flow_index) {
        case 0:
            myCom->setFlowControl(QSerialPort::NoFlowControl);
            break;
        case 1:
            myCom->setFlowControl(QSerialPort::HardwareControl);
            break;
        case 2:
            myCom->setFlowControl(QSerialPort::SoftwareControl);
            break;
        default:
            myCom->setFlowControl(QSerialPort::UnknownFlowControl);
            break;
        }
    }

    ~ComboboxToQt5Serialport()
    {

    }
};

#endif // COMBOBOXTOQT5SERIALPORT_H
