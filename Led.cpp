#include "Led.h"

Led::Led(QWidget *parent) :
    QLabel(parent)
{
    _activated = false;
    this->init();
}



Led::Led( bool activated, QWidget *parent) :
    QLabel(parent)
{
    _activated = activated;
    this->init();
}

void Led::init()
{
    this->setText("");
    this->setScaledContents( true );
    updateLed();
    this->setGeometry( this->x(), this->x(), DEFAULT_LED_SIZE, DEFAULT_LED_SIZE);
}

void Led::setSize(int w, int h)
{
    this->setGeometry( this->x(), this->x(), w, h);
}

void Led::on()
{
    setActivated( true );
}

void Led::off()
{
    setActivated( false );
}

void Led::toggle()
{
    setActivated( !(this->_activated) );
}
void Led::setActivated(bool activated)
{
    _activated = activated;
    updateLed();
}

void Led::updateLed()
{
    if ( _activated )
    {
        this->setPixmap(QPixmap(":/img/img/led_on.png"));
    }
    else
    {
        this->setPixmap(QPixmap(":/img/img/led_off_red.png"));
    }
    this->update();
}
