#include "Console.h"
#include "SerialPort.h"
#include "ui_Console.h"

Console::Console(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Console)
{
    ui->setupUi(this);
    connect( PolyboxModule::getInstance()->connector(), SIGNAL(dataReady()), this, SLOT(parseData()) );
    connect( PolyboxModule::getInstance()->connector(), SIGNAL(disconnected()), this, SLOT(deleteLater()) );
}

Console::~Console()
{
    delete ui;
}

void Console::parseData()
{
    ui->displaySerial->append(PolyboxModule::getInstance()->connector()->datas());
}

void Console::on_sendCodeButton_clicked()
{
    PolyboxModule::getInstance()->connector()->sendCode( ui->inputCode->text() );
    ui->inputCode->setText("");
}

void Console::on_inputCode_returnPressed()
{
    PolyboxModule::getInstance()->connector()->sendCode( ui->inputCode->text() );
    ui->inputCode->setText("");
}
