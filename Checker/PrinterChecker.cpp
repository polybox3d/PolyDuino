#include "PrinterChecker.h"
#include "ui_PrinterChecker.h"
#include <iostream>
using namespace std;

PrinterChecker::PrinterChecker(QWidget *parent) :
    AbstractChecker(parent),
    ui(new Ui::PrinterChecker)
{
    _printer = NULL;
    ui->setupUi(this);
}

PrinterChecker::PrinterChecker(PrinterModule* printer, QWidget *parent) :
    AbstractChecker(parent),
    ui(new Ui::PrinterChecker)
{
    _printer = printer;
    setModule(printer);
    ui->setupUi(this);

}

void PrinterChecker::setModule(PrinterModule *module)
{
    AbstractChecker::setModule( module );
    _printer = module;
    connect( _printer , SIGNAL(updateUI()), this, SLOT(updateUI()));
}

void PrinterChecker::updateModuleValues()
{
    _printer->updateComponents();
}

void PrinterChecker::updateUI()
{
    if ( _printer == NULL )
    {
        return;
    }
    else
    {
        //ui->tempBedExtLed->setActivated ( ! _printer->tempBedExt().isDefault() );
        //ui->tempBedExtValue->setText( _printer->tempBedExt().str() );

        ui->tempBedMidLed->setActivated ( !_printer->tempBedMid().isDefault()) ;
        ui->tempBedMidValue->setText ( _printer->tempBedMid().str() ) ;

        ui->tempBotBuse1Led->setActivated( !_printer->tempBotBuse1().isDefault() );
        ui->tempBotBuse1Value->setText( _printer->tempBotBuse1().str() );

        ui->tempBotBuse2Led->setActivated( !_printer->tempBotBuse2().isDefault());
        ui->tempBotBuse2Value->setText( _printer->tempBotBuse2().str());

        ui->tempTopBuse1Led->setActivated( !_printer->tempTopBuse1().isDefault() );
        ui->tempTopBuse1Value->setText( _printer->tempTopBuse1().str() );

        ui->tempTopBuse2Led->setActivated( !_printer->tempTopBuse2().isDefault() );
        ui->tempTopBuse2Value->setText( _printer->tempTopBuse2().str() );


        ui->tempBoxBotLed->setActivated( !_printer->tempBoxBot().isDefault() );
        ui->tempBoxBotValue->setText( _printer->tempBoxBot().str() );

        ui->tempBoxTopLed->setActivated( !_printer->tempBoxTop().isDefault() );
        ui->tempBoxTopValue->setText( _printer->tempBoxTop().str() );

        ui->tempBoxMiddleLed->setActivated( !_printer->tempBoxMiddle().isDefault() );
        ui->tempBoxMiddleValue->setText( _printer->tempBoxMiddle().str() );


        ui->coldBox1Led->setActivated( !_printer->coldBox1().isDefault() );
        ui->coldBox2Led->setActivated( !_printer->coldBox2().isDefault() );
        ui->coldBox3Led->setActivated( !_printer->coldBox3().isDefault() );
        ui->coldBox4Led->setActivated( !_printer->coldBox4().isDefault() );
        ui->coldBuse1Led->setActivated( !_printer->coldBuse1().isDefault() );
        ui->coldBuse2Led->setActivated( !_printer->coldBuse2().isDefault() );

        ui->printerPlugLed->setActivated( _printer->printerE0Plugged() );
        ui->printerPlugLed_2->setActivated( _printer->printerE1Plugged() );
        ui->bedPlugLed->setActivated( _printer->bedPlugged() );
        ui->detectPlasticLed->setActivated( _printer->detectPlastic() );

        ui->buseCloggedLed->setActivated( _printer->wireClogged() );

        ui->printerReadyLed->setActivated( _printer->isReady() );


    }

}

PrinterChecker::~PrinterChecker()
{
    delete ui;
}
