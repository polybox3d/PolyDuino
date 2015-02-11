#include "Temperature.h"

Temperature::Temperature()
{
    _value = DEFAULT_TEMP_VALUE;
    _mode = Celcius;
}
Temperature::Temperature(float temp)
{
    _value = temp;
    _mode = Celcius;
}

void Temperature::setValue(float temp)
{
    _value = temp;
}

void Temperature::setState( bool state )
{
    if ( !state )
    {
        _value = DEFAULT_TEMP_VALUE;
    }
    else
    {
        _value = 1;
    }
}

bool Temperature::isDefault() const
{
    return (_value >= DEFAULT_TEMP_VALUE-EPSYLON && _value <= DEFAULT_TEMP_VALUE+EPSYLON);
}

float Temperature::getValue() const
{
    return _value;
}

QString Temperature::str()
{
    if ( _mode == Celcius )
    {
        if ( isDefault() )
        {
            return "-";
        }
        else
        {
            return QString::number(_value)+"°C";
        }
    }
    else
    {
        return "";
    }
}
