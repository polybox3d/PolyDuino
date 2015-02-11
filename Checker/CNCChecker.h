#ifndef CNCCHECKER_H
#define CNCCHECKER_H

#include <QWidget>
#include <QPaintEvent>

#include "CNCModule.h"
#include "AbstractChecker.h"

namespace Ui {
class CNCChecker;
}
/**
 * @brief The CNCChecker class inherited from AbstractChecker. Display a checker for the CNCModule
 */
class CNCChecker : public AbstractChecker
{
    Q_OBJECT

public:
    /**
     * @brief CNCChecker Constructs a CNChecker inherited from AbstractChecker with a parent
     * @param parent the QWidget parent
     */
    explicit CNCChecker(QWidget *parent = 0);
    /**
     * @brief CNCChecker Constructs a CNChecker inherited from AbstractChecker with a cnc and a parent
     * @param cnc CNCModule to use for this checker.
     * @param parent QWidget
     */
    CNCChecker(CNCModule* cnc, QWidget *parent = 0);

    /**
     * @brief setModule overload function from AbstractChecker. Set up the fiven module as current CNCModule
     * @param module the CNCModule to use.
     */
    void setModule(CNCModule *module);
    /**
     * @brief updateModuleValues overload function, update the CNCModule contents by calling CNCModule.updateComponents();
     */
    void updateModuleValues();

    ~CNCChecker();

public slots:
    virtual void updateUI();
private:
    /**
     * @brief ui Graphical overlay
     */
    Ui::CNCChecker *ui;
    /**
     * @brief _cnc The CNCModule linked with the current checker. ui is updated based on this element.
     */
    CNCModule* _cnc;
};

#endif // CNCCHECKER_H
