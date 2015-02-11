#include "GlobalModule.h"

GlobalModule::GlobalModule(PolyboxModule *polybox, QObject *parent) :
    QObject(parent), AbstractModule(polybox)
{
    initAll();
}

void GlobalModule::initAll()
{
    _boxOpen = true;
    _ATUok = false;
    _arduino1 = false;
    _arduino2 = false;
    _arduino3 = false;
    _arduino4 = false;
    _command = false;
    _power = false;
    _webcamPlugged = false;
    _toolATUok = false;
    _preasiATUok = false;
    _icOpen = true;
}

void GlobalModule::parseMCode(QByteArray stream)
{
    QString str(stream);
    long value = SerialPort::embeddedstr2l( str, 0 );
    int idx = 0;
    int size = str.size();
    switch ( value )
    {
    case MCODE_GLOBAL_GET_BOX_OPEN:
    {
        SerialPort::nextField( str, idx);
        SerialPort::parseTrueFalse( &_boxOpen, str[idx] );  // Cuidao ! True = box is open, so Red light ! False means box is close, so gren light !
    }
    break;
    case 600:
    {
        SerialPort::nextField( str, idx);

        _ram = SerialPort::embeddedstr2l( str, idx );
    }
    break;
    case MCODE_GLOBAL_GET_STATUS:
    {
        SerialPort::nextField( str, idx);
        SerialPort::parseTrueFalse( &_ATUok, str[idx] );
    }
        break;
    case MCODE_GLOBAL_GET_ARDUINO_DETECTED: // Arduino1,2,3,4,... detected
    {
        while ( idx < size )
        {
            SerialPort::nextField( str, idx);
            if ( str[idx] == 'A')
            {
                if ( str[idx+1]=='1')
                {
                    SerialPort::nextValue( str, idx);
                    SerialPort::parseTrueFalse( &_arduino1, str[idx] );
                }
                else if ( str[idx+1]=='2')
                {
                    SerialPort::nextValue( str, idx);
                    SerialPort::parseTrueFalse( &_arduino2, str[idx] );
                }
                else if ( str[idx+1]=='3')
                {
                    SerialPort::nextValue( str, idx);
                    SerialPort::parseTrueFalse( &_arduino3, str[idx] );
                }
                else if ( str[idx+1]=='4')
                {
                    SerialPort::nextValue( str, idx);
                    SerialPort::parseTrueFalse( &_arduino4, str[idx] );
                }
            }
        }
    }
        break;
    case MCODE_GLOBAL_GET_POWER_STATUS:
    {
        while ( idx < size )
        {
            SerialPort::nextField( str, idx);
            if ( str[idx] == 'Z')
            {
                if ( str[idx+1]=='0')
                {
                    SerialPort::nextValue( str, idx);
                    SerialPort::parseTrueFalse( &_power, str[idx] );
                }
                else if ( str[idx+1]=='1')
                {
                    SerialPort::nextValue( str, idx);
                    SerialPort::parseTrueFalse( &_power, str[idx] );
                }
            }
        }
    }
        break;
    case 655:
    {
        while ( idx < size )
        {
            SerialPort::nextField( str, idx);
            if ( str[idx] == 'Z')
            {
                if ( str[idx+1]=='0')
                {
                    SerialPort::nextValue( str, idx);
                    SerialPort::parseTrueFalse( &_command, str[idx] );
                }
                else if ( str[idx+1]=='1')
                {
                    SerialPort::nextValue( str, idx);
                    SerialPort::parseTrueFalse( &_command, str[idx] );
                }
            }
        }
    }
    break;
    case MCODE_GLOBAL_GET_IC_TEMP:
    {
        SerialPort::nextField( str, idx);
        while ( idx < size )
        {
            if ( str[idx] == 'T' )
            {
                if ( str[idx+1] == '0' )
                {
                    SerialPort::nextValue( str, idx);
                    _tempIC.setValue(  SerialPort::embeddedstr2l( str, idx ) );
                }
            }
            SerialPort::nextField( str, idx);
        }
    }
    break;
    case MCODE_GLOBAL_GET_IC_OPEN:
    {
        SerialPort::nextField( str, idx);
        SerialPort::parseTrueFalse( &_icOpen, str[idx] );
    }
    break;
    case MCODE_GLOBAL_GET_TOOL_STATE: // tool bloc atu
    {
        SerialPort::nextField( str, idx);
        SerialPort::parseTrueFalse( &_toolATUok, str[idx] );
    }
    break;
    case MCODE_GLOBAL_GET_PREASI: // preasi atu
    {
        SerialPort::nextField( str, idx);
        SerialPort::parseTrueFalse( &_preasiATUok, str[idx] );
    }
    break;

    case 614:
    {
        /*SerialPort::nextField( str, idx);
        SerialPort::parseTrueFalse( &_, str[idx] );*/
    }
        break;
    default:
        break;
    }
    emit updateUI();
}

bool GlobalModule::isReady() const
{
    return !boxOpen() && arduinoMaitre() && ATUok() && arduino1() && arduino2() && arduino3() && arduino4() && power() && webcamPlugged() && command() && !(_tempIC.isDefault());
}

void GlobalModule::updateComponents()
{
    AbstractClient* connector = PolyboxModule::getInstance()->connector();
    _arduinoMaitre = connector->isConnected();
    connector->sendMCode(MCODE_GLOBAL_GET_BOX_OPEN);
    connector->sendMCode(MCODE_GLOBAL_GET_STATUS);
    connector->sendMCode(MCODE_GLOBAL_GET_ARDUINO_DETECTED);
    connector->sendMCode(MCODE_GLOBAL_GET_POWER_STATUS);
    connector->sendMCode(MCODE_GLOBAL_GET_IC_TEMP);
    connector->sendMCode(MCODE_GLOBAL_GET_IC_OPEN);
    connector->sendMCode(MCODE_GLOBAL_GET_PREASI);
    connector->sendMCode( 600 );

    emit updateUI();
}

bool GlobalModule::icOpen() const
{
    return _icOpen;
}
bool GlobalModule::preasiATUok() const
{
    return _preasiATUok;
}
bool GlobalModule::toolATUok() const
{
    return _toolATUok;
}

bool GlobalModule::boxOpen() const
{
    return _boxOpen;
}
bool GlobalModule::ATUok() const
{
    return _ATUok;
}
bool GlobalModule::arduinoMaitre() const
{
    return _arduinoMaitre;
}
bool GlobalModule::arduino1() const
{
    return _arduino1;
}
bool GlobalModule::arduino2() const
{
    return _arduino2;
}
bool GlobalModule::arduino3() const
{
    return _arduino3;
}
bool GlobalModule::arduino4() const
{
    return _arduino4;
}

bool GlobalModule::command() const
{
    return _command;
}
bool GlobalModule::power() const
{
    return _power;
}
bool GlobalModule::webcamPlugged() const
{
    return ! (LabViewModule::getAllCamera( Config::pathToWebcamDevice() ).empty()) ;
}

Temperature GlobalModule::tempIC()
{
    return _tempIC;
}
int GlobalModule::ram() const
{
    return _ram;
}
