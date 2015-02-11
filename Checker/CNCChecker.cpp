#include "CNCChecker.h"
#include "ui_CNCChecker.h"

CNCChecker::CNCChecker( QWidget *parent):
    AbstractChecker(parent),
    ui(new Ui::CNCChecker)
{
    _cnc = NULL;
    ui->setupUi(this);
}

CNCChecker::CNCChecker(CNCModule* cnc, QWidget *parent):
    AbstractChecker(parent),
    ui(new Ui::CNCChecker)
{
    _cnc = cnc;
    _currentModule = cnc;
    ui->setupUi(this);
}

void CNCChecker::setModule(CNCModule *module)
{
    AbstractChecker::setModule( module );
    _cnc = module;
    updateUI();
    connect( _cnc , SIGNAL(updateUI()), this, SLOT(updateUI()));
}
void CNCChecker::updateUI()
{
    if ( _cnc == NULL)
    {
        return;
    }
    else
    {
        ui->cncReadyLed->setActivated( _cnc->isReady() );
        ui->cncPlugLed->setActivated( _cnc->cncPlugged() );
        ui->motorLubLed->setActivated( _cnc->motorLubPlugged() );
        ui->levelLubLed->setActivated( _cnc->levelLub() );
        ui->vacuumLed->setActivated( _cnc->vacuumPlugged() );
        if ( _cnc->cncType() == Proxxon )
        {
            ui->proxonRadio->setEnabled( true );
            ui->proxonRadio->setChecked( true );
        }
        else if( _cnc->cncType() == Manual )
        {
            ui->manuelRadio->setEnabled( true );
            ui->manuelRadio->setChecked( true );
        }
        else
        {
            ui->proxonRadio->setEnabled( false );
            ui->proxonRadio->setChecked( false );
            ui->manuelRadio->setEnabled( false );
            ui->manuelRadio->setChecked( false );
        }
    }
}

void CNCChecker::updateModuleValues()
{
    _cnc->updateComponents();
}

CNCChecker::~CNCChecker()
{
    delete ui;
}

