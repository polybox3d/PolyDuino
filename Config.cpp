#include "Config.h"

#include <QStandardPaths>
#include <QDebug>

QString Config::pathToHomeDirectory()
{
    return QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
}

QString Config::defaultConfigFileName="./config.xml";


QColor Config::colorLabviewFaceSelected = QColor( 70, 230, 255 );
QString Config::ambiancePathFolder=":/xml/ambiances";



/**************************************************************************
 *              GUI_TIMER_GROUP
 * ***********************************************************************/

int Config::hardwareTimer()
{
    return Config::get(GUI_TIMER_GROUP,"hardwareTimer", 3000).toInt();
}
int Config::updateConfigModuleTimer()
{
return Config::get(GUI_TIMER_GROUP,"updateConfigModuleTimer", 500).toInt();
}
int Config::updateModuleTimer()
{
    return Config::get(GUI_TIMER_GROUP,"updateModuleTimer", 1000).toInt();
}



/**************************************************************************
 *              SETTINGS_GROUP
 * ***********************************************************************/


QString Config::runtimePath()
{
    return Config::get(SETTINGS_GROUP,"runtimePath", "../../").toString();
}

QString Config::broadcastIP()
{
    return Config::get(SETTINGS_GROUP,"broadcastIP", "127.0.0.1").toString();
}

int Config::broadcastPort()
{
    return Config::get(SETTINGS_GROUP,"broadcastPort", "6842").toInt();
}

void Config::setBroadcastIP(QString IP)
{
    Config::set(SETTINGS_GROUP,"broadcastIP", IP);
}
void Config::setBroadcastPort(int port)
{
    Config::set(SETTINGS_GROUP,"broadcastPort", port);
}

QString Config::pathToConfigFile()
{
    return "Configurations";
}

QString Config::translationPath()
{
    return Config::get(SETTINGS_GROUP,"translationPath", Config::runtimePath()+"i18n").toString();
}

QString Config::pathToDropbox()
{
    return Config::get(SETTINGS_GROUP,"pathToDropbox",Config::pathToHomeDirectory()+"plbx-dropbox/").toString();
}

bool Config::bypassCheck()
{
    return Config::get(SETTINGS_GROUP,"bypassCheck", true).toBool();
}
bool Config::blockedConnectionThread()
{
    return Config::get(SETTINGS_GROUP,"blockedConnectionThread", true).toBool();
}

/**************************************************************************
 *              GLOBAL_GROUP
 * ***********************************************************************/
float Config::webCamRotation()
{
    return Config::get(GLOBAL_GROUP,"webCamRotation", 0).toFloat();
}
/**************************************************************************
 *              CONNECTION_GROUP
 * ***********************************************************************/

QString Config::pathToSerialDevice()
{
    return Config::get(CONNECTION_GROUP,"pathToSerialDevice", "/dev/").toString();
}

QString Config::pathToVirtualPolySerialDevice()
{
    return Config::get(CONNECTION_GROUP,"pathToVirtualPolySerialDevice", "/dev/").toString();
}
QString Config::serialVirtualPolySerialPort()
{
    return Config::get(CONNECTION_GROUP,"serialVirtualPolySerialPort", "ttyPOLY").toString();
}
QString Config::pathToWebcamDevice()
{
    return Config::get(CONNECTION_GROUP,"pathToWebcamDevice", "/dev/").toString();
}

QString Config::serialPortName()
{
    return Config::get(CONNECTION_GROUP,"serialPortName", "ttyACM0").toString();
}

QString Config::pathToPolyplexerDaemon()
{
    return Config::get(CONNECTION_GROUP,"pathToPolyplexerDaemon", Config::runtimePath()+"externals/Polyplexer/PolyPlexer").toString();
}
int Config::connectionUptimeDelay()
{
    return Config::get(CONNECTION_GROUP,"connectionUptimeDelay", 1000).toInt();
}
int Config::motherboardBaudrate()
{
    return Config::get(CONNECTION_GROUP,"motherboardBaudrate", 115200).toInt();
}

bool Config::disablePolyplexer()
{
    return Config::get(CONNECTION_GROUP,"disablePolyplexer", false).toBool();
}

QHostAddress Config::serverListeningAddress()
{
    QString s = Config::get(CONNECTION_GROUP,"serverListeningAddress", "127.0.0.1").toString();
    QHostAddress h(s);
    return h;
}

quint16 Config::serverListeningPort()
{
    return Config::get(CONNECTION_GROUP,"serverListeningPort", "8862").toInt();
}

/**************************************************************************
 *              SCANNER_GROUP
 * ***********************************************************************/

/**************************************************************************
 *              CNC_GROUP
 * ***********************************************************************/

QString Config::pathToLinuxCNC()
{
    return Config::get(CNC_GROUP,"pathToLinuxCNC", Config::pathToHomeDirectory()+"linuxcnc/").toString();
}
QString Config::linuxCNCCommand()
{
    return Config::get(CNC_GROUP,"linuxCNCCommand", "linuxcnc").toString();
}
QString Config::linuxCNCConfig()
{
    return Config::get(CNC_GROUP,"linuxCNCConfig", Config::pathToHomeDirectory()+"linuxcnc/configs/mesa_official1/mesa_official1.ini").toString();
}

QString Config::linuxCNCDefaultConfigFile()
{
    return Config::get(CNC_GROUP,"linuxCNCDefaultConfigFile", Config::linuxCNCConfig()+"/mesa_official1/mesa_official1.ini").toString();
}
void Config::setLinuxCNCDefaultConfigFile(QString ini_file)
{
    if ( QFile::exists( ini_file ) )
    {
        Config::set(CNC_GROUP,"linuxCNCDefaultConfigFile", ini_file);
    }
}

/**************************************************************************
 *              PRINTER_GROUP
 * ***********************************************************************/

QString Config::pathToPrinterSoftware()
{
    return Config::get(PRINTER_GROUP, "pathToPrinterSoftware",
                Config::pathToHomeDirectory()+"Dev/reprapgiga/Repetier-HostModified/Repetier-Host-master/src/RepetierHost/bin/Release/RepetierHost.exe" ).toString();
}
void Config::setPathToPrinterSoftware( QString path_to_printer_software)
{
    if ( QFile::exists( path_to_printer_software ) )
    {
        Config::set(PRINTER_GROUP,"pathToPrinterSoftware", path_to_printer_software);
    }
}

QString Config::pathToPrinterWorkingDir()
{
    return Config::get(PRINTER_GROUP, "pathToPrinterWorkingDir",
                Config::pathToHomeDirectory()+"Dev/reprapgiga/RepetierHost" ).toString();
}

float Config::bedTempPla()
{
    return Config::get(PRINTER_GROUP,"bedTempPla", 50).toInt();

}
float Config::bedTempAbs()
{
    return Config::get(PRINTER_GROUP,"bedTempAbs", 70).toInt();

}
float Config::bedTempNylon()
{
    return Config::get(PRINTER_GROUP,"bedTempNylon", 65).toInt();
}

QString Config::pathToJoypadOverlay=Config::pathToHomeDirectory()+"joypadoverlay/src/JoypadOverlay";



Config::Config()
{
}


void Config::init()
{
    QSettings().setValue("LOG/nbrExec", QSettings().value("LOG/nbrExec").toInt() + 1 );
    QSettings().setValue("ABOUT/version", QCoreApplication::applicationVersion() );
    // no settings found
    if ( QSettings().value(QString(SETTINGS_GROUP)+"/runtimePath").toString().isEmpty() )
    {
        // We must find the runtime path (means we want the top level of the git repository
        QDir dir;
        for ( u_int8_t i = 0 ; i < 6 ; ++i )
        {

            if ( dir.cd("src") )
            {
                dir.cdUp();
                Config::get(SETTINGS_GROUP,"runtimePath", dir.path()+"/").toString();
                return;
            }
            else
            {
                dir.cdUp();
            }
        }
        Config::get(ERRORS_GROUP,"runtimePath", "CRITICAL : Can't find src directory... The software will not work.").toString();
    }
}
