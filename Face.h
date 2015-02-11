#ifndef FACE_H
#define FACE_H

#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QColor>
#include <QTimer>

#include "SerialPort.h"
#include "mcode.h"
#include "PolyboxModule.h"

#include <iostream>

using namespace std;


#define FACE_RIGHT_ID 0
#define FACE_BACK_ID 1
#define FACE_LEFT_ID 2
#define FACE_TOP_ID 3
#define FACE_FRONT_ID 4

#define FACE_BOT_ID 5

class Face : public QObject
{
    Q_OBJECT
public:
    explicit Face();
    ~Face();
    QString name;
    int id;

    void setHIntensity( int h );
    void setVIntensity( int v );

    void sendIntensity();

    void setColor( int r, int g, int b);
    void setColor( QColor c);
    void sendColor();
    QColor color(){ return _color; }
    QColor* getColor(){ return &_color; }

    int h();
    int v();

    void toXml( QXmlStreamWriter* xml );

    static int defaultLight;

public slots:
    void sendValues();
private:

    void startSenderTimer( int msec = 500);

    int _h;
    int _v;
    QColor _color;
    QTimer _updateTimer;

};

#endif // FACE_H
