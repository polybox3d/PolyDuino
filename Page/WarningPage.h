#ifndef WARNING_H
#define WARNING_H

#include <QWidget>
#include <QTimer>
#include <QDesktopServices>

#include "MainWindow.h"
#include "CNCChecker.h"
#include "SCannerChecker.h"
#include "PrinterChecker.h"
#include "GlobalChecker.h"
#include "HomeButton.h"
#include "Console.h"

#include "PolyboxModule.h"

namespace Ui {
class WarningPage;
}
/**
 * @brief The WarningPage class Constructs a QWidget page grouping all the checker (cnc, scanner, global, printer)
 * Futhermore, allo wthe user to change some software value (constant, path etc..) and run some tests
 */
class WarningPage : public QWidget
{
    Q_OBJECT

public:
    explicit WarningPage(PolyboxModule* polybox, QWidget *parent = 0);
    ~WarningPage();

public slots:

    /**
     * @brief goBack Go back to the previous page
     */
    void updateModules();
private slots:
    /**
     * @brief on_configuration_clicked Called when the user click on Configuration button. Open a DialogConfigSoft pop-up to ask for some information.
     */
    void on_configuration_clicked();

    void on_console_clicked();

    void on_pinEditor_clicked();

private:
    /**
     * @brief ui Graphical Layer.
     */
    Ui::WarningPage *ui;
    /**
     * @brief _polybox pending PolyboxModule.
     */
    PolyboxModule* _polybox;
    QTimer _updateComponentsTimer;
};

#endif // WARNING_H
