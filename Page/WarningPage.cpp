#include "WarningPage.h"
#include "DebugPin.h"
#include "ui_WarningPage.h"

WarningPage::WarningPage(PolyboxModule *polybox, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WarningPage)
{
    ui->setupUi(this);
    _polybox = polybox;
    _updateComponentsTimer.start( Config::updateConfigModuleTimer()  );
    connect( &_updateComponentsTimer, SIGNAL(timeout()), this, SLOT(updateModules()));
    HomeButton* hb = new HomeButton( 50,50, this );
    hb->setGeometry( this->width()-hb->width()-10,
                     this->height()-hb->height(),
                     hb->width(), hb->height());
    connect( hb, SIGNAL(clicked()), PolyboxModule::getInstance(), SLOT(connectionSlot()));

    ui->generalWidget->setModule( _polybox->globalModule() );
    ui->scannerWidget->setModule( _polybox->scannerModule() );
    ui->cncWidget->setModule( _polybox->cncModule() );
    ui->printerWidget->setModule( _polybox->printerModule() );

}
void WarningPage::updateModules()
{
    bool running;
    running = PolyboxModule::getInstance()->isConnected();

    ui->generalWidget->setEnabled( running );
    ui->scannerWidget->setEnabled( running );
    ui->cncWidget->setEnabled( running );
    ui->printerWidget->setEnabled( running );
    ui->console->setEnabled( running );
    ui->pinEditor->setEnabled( running );

    if ( running )
    {
        ui->generalWidget->updateModuleValues();
        ui->scannerWidget->updateModuleValues();
        ui->cncWidget->updateModuleValues();
        ui->printerWidget->updateModuleValues();
    }



}

WarningPage::~WarningPage()
{
    delete ui;
}

void WarningPage::on_configuration_clicked()
{
    QDesktopServices::openUrl(QUrl(Config::pathToConfigFile()+"/"+QCoreApplication::organizationName()+"/"+QCoreApplication::applicationName()+".conf"));
}

void WarningPage::on_console_clicked()
{
    //MainWindow::getMainWindow()->startConsoleWindow();

}

void WarningPage::on_pinEditor_clicked()
{
    DebugPin* debugpin = new DebugPin();
    debugpin->setWindowTitle(tr("Editeur de pins"));
    debugpin->show();
}
