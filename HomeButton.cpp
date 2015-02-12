#include "HomeButton.h"

HomeButton::HomeButton(QWidget *parent) :
    QPushButton(parent)
{
    changeIconOnConnectorType(PolyboxModule::getInstance()->connectorType());
    setText("");
    setIconSize( QSize(this->width(), this->height()) );
    //setGeometry(0,0,160,160);
    setFlat( true );
}


HomeButton::HomeButton( int w, int h, QWidget *parent) :
    QPushButton(parent)
{
    changeIconOnConnectorType(PolyboxModule::getInstance()->connectorType());
    setText("");
    setSize( w, h);
    setFlat( true );
    connect(PolyboxModule::getInstance(),
            SIGNAL(newType(PolyboxModule::ConnectorType)),
            this,
            SLOT(changeIconOnConnectorType(PolyboxModule::ConnectorType)));
}

void HomeButton::setSize(int w, int h)
{
    setGeometry(0,0,w,h);
    setIconSize( QSize(w, h) );
}


void HomeButton::changeIcon(QPixmap img)
{
    setIcon(img);
    setIconSize( QSize(this->width(), this->height()) );
}

void HomeButton::changeIconOnConnectorType(PolyboxModule::ConnectorType type)
{
    if ( type == PolyboxModule::ServerTCP)
    {
        changeIcon( QPixmap(":/img/img/logo_400_blu.png") );
    }
    else if ( type == PolyboxModule::CLientTCP)
    {
        changeIcon( QPixmap(":/img/img/logo_400_yellow.png") );
    }
    else //if ( type == Serial)
    {
        changeIcon( QPixmap(":/img/img/logo_400.png") );
    }
}
