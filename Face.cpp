#include "Face.h"

int Face::defaultLight=0;

Face::Face(): QObject(0)
{
    id = 0;
    name = "default-face";
    _v = defaultLight;
    _h = defaultLight;

    _updateTimer.setSingleShot(true);
    connect(&_updateTimer, SIGNAL(timeout()),this,SLOT(sendValues()));
}
Face::~Face()
{

}


void  Face::toXml(QXmlStreamWriter *xml)
{
    xml->writeStartElement("face");
    xml->writeAttribute("name", name);
    xml->writeTextElement("horizontale", QString::number(_h) );
    xml->writeTextElement("verticale", QString::number(_v) );
    xml->writeEndElement();
}


void Face::setColor( int r, int g, int b)
{
    setColor( QColor(r,g,b) );
}

void Face::startSenderTimer(int msec)
{
    _updateTimer.start( msec );
}

void Face::setColor( QColor c)
{
    _color = c;
    startSenderTimer( 500 );
    //sendColor();
}

void Face::sendValues()
{
    sendColor();
    sendIntensity();
}

void Face::sendColor()
{
    PolyboxModule::getInstance()->connector()->sendMCode(QString::number(MCODE_LABVIEW_SET_FACE_RGB)
                                       +" S"+QString::number(this->id)
                                       +" R"+QString::number(_color.red())
                                       +" E"+QString::number(_color.green())
                                       +" P"+QString::number(_color.blue())
                                       +" I"+QString::number(_color.alpha()));
}


void Face::setHIntensity( int h )
{
    _h = h;
    startSenderTimer( 500 );
    //sendIntensity();
}

void Face::setVIntensity( int v )
{
    _v = v;
    startSenderTimer( 500 );
}
void Face::sendIntensity()
{
    PolyboxModule::getInstance()->connector()->sendMCode(QString::number(MCODE_LABVIEW_SET_FACE_I)+" S"+QString::number(id)+" X"+QString::number(_h)+" Y"+QString::number(_v));
}

int Face::h()
{
    return _h;
}

int Face::v()
{
    return _v;
}
