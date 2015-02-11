#include "SerialPort.h"
#include <QDebug>
#include <string.h>
#include <iostream>

using namespace std;

SerialPort* SerialPort::serialPortInstance = NULL;

SerialPort::SerialPort(QObject *parent) :
    AbstractClient(parent)
  //QextSerialPort("/dev/ttyACM0", QextSerialPort::EventDriven, parent)
{
    _path = "/dev/";
    _name = "ttyACM0";
}

QString SerialPort::path()
{
    return _path;
}
QString SerialPort::name()
{
    return _name;
}
void SerialPort::setName( QString name )
{
    _name = name;
}

void SerialPort::setPath(QString path)
{
    _path = path;
}

bool SerialPort::connectToSerialPort()
{
    disconnectPort();
    _connector = new QextSerialPort(_path+_name, QextSerialPort::EventDriven);

    QextSerialPort* port = static_cast<QextSerialPort*>(_connector);
    port->setBaudRate( (BaudRateType)(115200) );
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);

    if ( port->open(QIODevice::ReadWrite) == true)
    {
        //connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()) );
        //      connect(this, SIGNAL(dsrChanged(bool)), this, SLOT(onDsrChanged(bool)) );
     /*   if (!(lineStatus() & LS_DSR)){
            qDebug() << "warning: device is not turned on"<<lineStatus();
            return false;
        }*/

        this->startConnection();
        return true;
    }
    else
    {
        qDebug() << "device failed to open:" << port->errorString();
        return false;
    }

}

QextSerialPort* SerialPort::getConnector()
{
    return static_cast<QextSerialPort*>(_connector);
}

void SerialPort::disconnectPort()
{
    QextSerialPort* port = SerialPort::getConnector();
    if ( port != NULL && port->isOpen() )
    {
        this->sendMCode( MCODE_END_CONNECTION );
        port->flush();
        port->close();
        emit disconnected();
    }
}

