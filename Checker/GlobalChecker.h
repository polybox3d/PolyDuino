#ifndef GLOBALCHECKER_H
#define GLOBALCHECKER_H

#include <QWidget>

#include "AbstractChecker.h"
#include "GlobalModule.h"

namespace Ui {
class GlobalChecker;
}
/**
 * @brief The GlobalChecker class Inherited from AbstractChecker. Check global status, like ATU, if the box is open or if all arduino are detected.
 */
class GlobalChecker : public AbstractChecker
{
    Q_OBJECT

public:
    /**
     * @brief GlobalChecker Constructs a checker based of AbstractChecker with a parent.
     * @param parent parent QWidget.
     */
    explicit GlobalChecker(QWidget *parent = 0);
    /**
     * @brief GlobalChecker Constructs a checker based of AbstractChecker with a parent.
     * @param global
     * @param parent
     */
    explicit GlobalChecker(GlobalModule* global, QWidget *parent = 0);

    virtual void setModule( GlobalModule* module );
    virtual void updateModuleValues();

    virtual ~GlobalChecker();

public slots:
    void updateUI();
private:
    /**
     * @brief ui Graphical layer.
     */
    Ui::GlobalChecker *ui;
    GlobalModule* _global;
};

#endif // GLOBALCHECKER_H
