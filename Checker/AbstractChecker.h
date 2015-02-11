#ifndef ABSTRACTCHECKER_H
#define ABSTRACTCHECKER_H

#include "AbstractModule.h"
#include "ScannerModule.h"
#include "CNCModule.h"

#include <iostream>
#include <QWidget>

/**
 * @brief The AbstractChecker class herite from QWidget. It provide an abstract class for checker linked with an AbstractModule.
 * The herited checker should show a UI, with, for example some led, and label displaying AbstractModule contents.
 */

class AbstractChecker : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief AbstractChecker Construct an abstract checker with a parent
     * @param parent QWidget parent.
     */
    explicit AbstractChecker(  QWidget* parent=0): QWidget(parent) { _currentModule = NULL; }
    virtual ~AbstractChecker(){}
    /**
     * @brief setModule set the @AbstractModule.
     * @param module @AbstractModule
     */
    virtual void setModule( AbstractModule* module ){
        _currentModule = module;
    }
    /**
     * @brief updateModuleValues virtual class. It's update the stored AbstractModule. Should be implemented by herited sub-class.
     */
    virtual void updateModuleValues() {}
public slots:
    virtual void updateUI(){}
protected:
    /**
     * @brief _currentModule , actually, a bit useless due some co(s)mics reasons.
     */
    AbstractModule* _currentModule;
};

#endif // ABSTRACTCHECKER_H
