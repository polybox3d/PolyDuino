#ifndef PRINTERCHECKER_H
#define PRINTERCHECKER_H

#include <QWidget>

#include "PrinterModule.h"
#include "Temperature.h"
#include "AbstractChecker.h"

namespace Ui {
class PrinterChecker;
}

class PrinterChecker : public AbstractChecker
{
    Q_OBJECT

public:
    explicit PrinterChecker(QWidget *parent = 0);
    PrinterChecker(PrinterModule* printer, QWidget *parent = 0);
    void setModule(PrinterModule *module);
    void updateModuleValues();

    ~PrinterChecker();

public slots:
    void updateUI();
private:
    Ui::PrinterChecker *ui;

    PrinterModule* _printer;
};

#endif // PRINTERCHECKER_H
