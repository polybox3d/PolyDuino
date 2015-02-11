#ifndef ABSTRACTMODULE_H
#define ABSTRACTMODULE_H

#include <iostream>
using namespace std;

#include "PolyboxModule.h"

/**
 * @brief The AbstractModule class is an Abstract class for module sub-class.
 * Allow the user to check the state of the module (isReady) or update his components.
 */
class AbstractModule
{

public:
    /**
     * @brief AbstractModule Constructs an abstract module with a PolyboxModule as parameter.
     * @param polybox pointer to the current PolyboxModule.
     */
    AbstractModule(PolyboxModule* polybox){ _polybox = polybox; _isOn = true; initAll();}
    virtual ~AbstractModule(){ }

    /**
     * @brief isReady a pure virtual method. Needs to be implemented by inherited class. Return the current state of the module.
     *
     * @return Return True if the module is  Ready, i.e, connected, all components ready etc..
     * Return False if something is wrong, like for example, a wire is unplugged, or if the device is not connected.
     */
    virtual bool isReady() const = 0;
    virtual void updateComponents() =0;
    virtual void parseMCode(QByteArray stream)=0;
    bool isOn() const
    {
        return _isOn;
    }

protected:
    /**
     * @brief initAll initialize all components with default values (false for bolean)
     */
    virtual void initAll(){ }
    void resetAll(){ initAll(); }
    /**
     * @brief _polybox Pointer to the pending PolyboxModule. Can be used to send datas through /dev/tty or access to some values.
     */
    PolyboxModule* _polybox;
    bool _isOn;
private:
};

#endif // ABSTRACTMODULE_H
