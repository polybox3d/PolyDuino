#ifndef POLYBOXMODULE_H
#define POLYBOXMODULE_H

#include <QObject>
#include <QByteArray>
#include <QTimer>
#include <QProcess>

#include "Config.h"
#include "mcode.h"
#include "SerialPort.h"
#include "ClosedLoopTimer.h"

/*#include "LabViewModule.h"
#include "CNCModule.h"
#include "ScannerModule.h"
#include "PrinterModule.h"
*/

class CNCModule;
class LabViewModule;
class PrinterModule;
class ScannerModule;
class GlobalModule;

class PolyboxModule : public QObject
{
    Q_OBJECT
public:

    enum ConnectorType{ Serial, ServerTCP, CLientTCP, Abstract};
    enum ConnectionStatus{ Connected=0, ErrorPolyplexer=2, ErrorConnection=4, Permission=8, NotFound=16, TimeOut=32};

    static PolyboxModule* getInstance(QObject *parent=0);

    ConnectorType connectorType() const;
    void setConnectorType( ConnectorType type);
    bool isCommonReady();
    static bool isConnected();
    bool isCncReady();
    bool isPrinterReady();
    bool isScannerReady();
    GlobalModule* globalModule();
    CNCModule* cncModule();
    LabViewModule* labViewModule();
    ScannerModule* scannerModule();
    PrinterModule* printerModule();

    ConnectionStatus connection( bool blocked_thread=false);
    ConnectionStatus connectionGUI( bool blocked_thread=false);
    void setupConnection(QString path, QString port);

    AbstractClient* connector();
    void setConnector( AbstractClient* connector, ConnectorType type = Abstract );

signals:
    void updateHardware();
    void newType(PolyboxModule::ConnectorType type);

public slots:
    void parseData();
    void hardwareTimerTimeout();
    void connectionSlot();


private:
    bool _connected;
    PolyboxModule(QObject *parent = 0);
    static PolyboxModule* polyboxModuleInstance;

    u_int8_t _numberOfMissingPingPong;
    GlobalModule* _global;
    CNCModule* _cnc;
    LabViewModule* _labview;
    ScannerModule* _scanner;
    PrinterModule* _printer;
    AbstractClient * _connector;
    QTimer _hardwareTimer;
    QTimer _pingPongTimer;
    void parseMCode( QByteArray stream );
    ConnectorType _connectorType;
    QProcess* _virtuSerial;

};

#endif // POLYBOXMODULE_H
