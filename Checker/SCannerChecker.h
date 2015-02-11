#ifndef SCANNERCHECKER_H
#define SCANNERCHECKER_H

#include <QWidget>
#include <QPaintEvent>

#include "ScannerModule.h"
#include "AbstractChecker.h"

namespace Ui {
class SCannerChecker;
}

class SCannerChecker : public AbstractChecker
{
    Q_OBJECT

public:
    explicit SCannerChecker(QWidget *parent = 0);
    SCannerChecker(ScannerModule* scanner, QWidget *parent = 0);
    void setModule(ScannerModule* module);
    void updateModuleValues();

    ~SCannerChecker();
public slots:
    void updateUI();

private:
    Ui::SCannerChecker *ui;

    ScannerModule* _scanner;
};

#endif // SCANNERCHECKER_H
