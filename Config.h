#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QColor>

#include <QSettings>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMap>
#include <QDir>
#include <QDate>
#include <QCoreApplication>
#include <QHostAddress>

#include <iostream>

using namespace std;

/**
 * @brief The Config class Store Polybox config and constants, such as program path, command, driver.
 */
class Config
{
public:
//#define INITIAL_CONFIG_FILE ":/xml/config/.initialConfig.xml"

#define PRINTER_GROUP "PRINTER"
#define CNC_GROUP "CNC"
#define SCANNER_GROUP "SCANNER"
#define GLOBAL_GROUP "GLOBAL"
#define SETTINGS_GROUP "SETTINGS"
#define CONNECTION_GROUP "CONNECTION"
#define GUI_TIMER_GROUP "GUI_TIMER"
#define ERRORS_GROUP "ERRORS"
#define QSETTINGS_LOAD_AND_SAVE 1

#define POWER_SUPPLY_ENABLE_PIN_0 51 // pin 51 master
#define POWER_SUPPLY_ENABLE_PIN_1 28+(70*1) // pin 28 slave 1

    Config();
    static QString translationPath();
    static QString pathToDropbox();

    static QString runtimePath();

    /**
     * @brief pathToHomeDirectory Full path to the main user home directory (/home/<user>/)
     */
    static QString pathToHomeDirectory();
    /**
     * @brief pathToWebcamDevice Full path to the device directory. Something like /dev/tty for linux
     */
    static QString pathToWebcamDevice();

    static QString pathToSerialDevice();

    static QString serialPortName();

    static QString pathToPolyplexerDaemon();

    static QString pathToVirtualPolySerialDevice();

    static QString serialVirtualPolySerialPort();
    static QString pathToConfigFile();

    static QHostAddress serverListeningAddress();
    static quint16 serverListeningPort();

    /**
     * @brief motherboardBaudrate Default baudrate between software and Polybox.
     */
    static int motherboardBaudrate();

    static int connectionUptimeDelay();

    /**
     * @brief pathToLinuxCNC Full path to the top-level linuxCNC folder.
     */
    static QString pathToLinuxCNC();
    /**
     * @brief linuxCNCCommand Command to start linuxCNC
     */
    static QString linuxCNCCommand();
    /**
     * @brief linuxCNCConfig configuration to parse. Path to config folder. Should be ~/linuxcnc/config
     */
    static QString linuxCNCConfig();

    static QString linuxCNCDefaultConfigFile();
    static void setLinuxCNCDefaultConfigFile( QString ini_file);

    /**
     * @brief bypassCheck disable check, so the user can acces to everything, withotu printer/cnc controle (atu, NTC, etc...)
     */
    static bool bypassCheck();
    static bool blockedConnectionThread();


    static bool disablePolyplexer();

    /**
     * @brief colorLabviewFaceSelected Color used when a face is selected in the labview module.
     */
    static QColor colorLabviewFaceSelected;
    /**
     * @brief ambiancePathFolder Path to the default ambiance directory. Ambiances are XML files for labview profiles.
     */
    static QString ambiancePathFolder;

    static QString defaultConfigFileName;

    static QString pathToJoypadOverlay;

    static float webCamRotation();

    static float bedTempPla();
    static float bedTempAbs();
    static float bedTempNylon();

    static int hardwareTimer();
    static int updateConfigModuleTimer();
    static int updateModuleTimer();

    static int broadcastPort();
    static QString broadcastIP();

    static void setBroadcastPort( int port );
    static void setBroadcastIP( QString IP );

    static QString pathToPrinterSoftware();
    static void setPathToPrinterSoftware( QString path_to_printer_software );
    static QString pathToPrinterWorkingDir();

    static void set(QString group_name, QString key, const QVariant &value )
    {
         QSettings().setValue( group_name+"/"+key, value );
    }

    static QVariant get(QString group_name, QString key, const QVariant &defaultValue = QVariant() )
    {
        //QSettings().beginGroup(group_name);
        QVariant v = QSettings().value( group_name+"/"+key, defaultValue );
        //QSettings().endGroup();

#ifdef QSETTINGS_LOAD_AND_SAVE
  #if QSETTINGS_LOAD_AND_SAVE == 1
        // Save default value
        if ( v == defaultValue )
        {
            Config::set( group_name, key, defaultValue );
        }
  #endif
#endif
        return v;
    }

    static void init();

    static void importFromXmlFile( QString filename );
    static void saveToXmlFile( QString filename );
    static void parseGeneral(QXmlStreamReader *xml);
    static void parseCNC(QXmlStreamReader *xml);
    static void parsePrinter(QXmlStreamReader *xml);
    static void parseWebcam(QXmlStreamReader *xml);


};

#endif // CONFIG_H
