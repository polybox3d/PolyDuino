#ifndef CNCMODULE_H
#define CNCMODULE_H

#include <QObject>
#include <QDir>
#include <QDirIterator>

#include "AbstractModule.h"
#include "mcode.h"
/**
 * @brief The CNCType enum List of all available CNCTool Type.
 */
enum CNCType
{
    Noone, Proxxon, Manual, Unknowed
};


#define DEFAULT_LEVEL_LUB -42.42
/**
 * @brief The CNCModule class inherited of AbstractModule. Provide a class to handle CNC.
 */
class CNCModule : public QObject, public AbstractModule
{
    Q_OBJECT
public:
    /**
     * @brief CNCModule Constreucts a class based on AbstractModule with a polybox as parameter and a parent.
     * @param polybox
     * @param parent
     */
    explicit CNCModule(PolyboxModule* polybox, QObject *parent = 0);
    ~CNCModule();

    /**
     * @brief isReady Informe if the CNCModule is ready to be used. If everything is connected etc..
     * @return Return True if the moduel is ready, false otherwise.
     */
    virtual bool isReady() const;
    /**
     * @brief updateComponents Updates contents, like temps, tools's status. Retreive data from serial communication.
     */
    virtual void updateComponents();

    /**
     * @brief cncPlugged Return Ture if the CNC is plugged.
     * @return
     */
    bool cncPlugged();
    /**
     * @brief motorLubPlugged Returns the motor's status. Is the motor plugged ?
     * @return Return True if the lubricant motor is plugged, False otherwise.
     */
    bool motorLubPlugged();
    /**
     * @brief levelLub Return the current lubricant level inside the CNC.
     * @return Return the current lubricant level inside the CNC.
     */
    float levelLub();
    /**
     * @brief vacuumPlugged Returns the vacuum's status. Is the vacuum plugged ?
     * @return True if the vacuum is plugged, False otherwise.
     */
    bool vacuumPlugged();
    /**
     * @brief cncType Get the current Type of CNCTool used. See enum CNCType.
     * @return The current CNCTool type. Return CNCType::Noone by default.
     */
    CNCType cncType();

    virtual void parseMCode(QByteArray stream);


    void updateGlobalStatus();
    void updateToolPlugged();
    void updateLubricantLevel();
    void updateVacummPlugged();

signals:
    void updateUI();

private:
    /**
     * @brief initAll Initilalize all components.
     */
    virtual void initAll();

    bool _cncPlugged;
    bool _motorLubPlugged;
    float _levelLub;
    bool _vacuumPlugged;
    CNCType _cncType;
    /**
     * @brief _linuxcnc Stores the linuxcnc process. (external software, see Config::linuxCNCCommand for futher information)
     */
    QProcess* _linuxcnc;

};

#endif // CNCMODULE_H
