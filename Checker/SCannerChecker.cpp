#include "SCannerChecker.h"
#include "ui_SCannerChecker.h"

SCannerChecker::SCannerChecker(QWidget *parent) :
    AbstractChecker(parent),
    ui(new Ui::SCannerChecker)
{
    _scanner = NULL;
    _currentModule = NULL;
    ui->setupUi(this);
}

SCannerChecker::SCannerChecker(ScannerModule* scanner, QWidget *parent) :
    AbstractChecker(parent),
    ui(new Ui::SCannerChecker)
{
    setModule( scanner );
    _scanner = scanner;
    ui->setupUi(this);
}

void SCannerChecker::setModule(ScannerModule* module)
{
    AbstractChecker::setModule( module );
    _scanner = module;
    connect( _scanner , SIGNAL(updateUI()), this, SLOT(updateUI()));
}

void SCannerChecker::updateModuleValues()
{
    _scanner->updateComponents();
}

void SCannerChecker::updateUI()
{
    if ( _scanner == NULL )
    {
        return;
    }
    else
    {
        ui->webcamPlugLed->setActivated( _scanner->webcamPlugged() );
        ui->turntableLed->setActivated( _scanner->turntablePlugged() );

        ui->laser0Led->setActivated( _scanner->laser0Plugged() );
        ui->laser1Led->setActivated( _scanner->laser1Plugged() );
        //ui->turntableLed_2->setActivated( _scanner->turntablePlugged() );
        //ui->primesencePlugLed->setActivated( _scanner->primesensePlugged() );
    }
}

SCannerChecker::~SCannerChecker()
{
    delete ui;
}
