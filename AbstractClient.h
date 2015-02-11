#ifndef ABSTRACTCLIENT_H
#define ABSTRACTCLIENT_H

#include <QObject>
#include <QByteArray>
#include <QTimer>
#include <QIODevice>

class AbstractClient : public QObject
{
    Q_OBJECT
public:
    explicit AbstractClient(QObject *parent = 0);


    int connectionUptime;
    QByteArray datas();
    virtual bool isConnected() const;

    virtual QIODevice* getConnector();

    /**
     * @brief sendMCode Send code value as M Code to the device connected.
     * @param code
     */
    void sendMCode(QString code);
    void sendMCode(int code);
    void sendCode(QString code);
    void startConnection();

protected:
    QByteArray _datas;
    QByteArray _rcp_datas;
    QTimer _uptimeTimer;

signals:
    void dataReady();
    void disconnected();

public slots:
    void parseSerialDatas();
    void connectionUptimeProcess();

protected:
    QIODevice* _connector;
};

#endif // ABSTRACTCLIENT_H
