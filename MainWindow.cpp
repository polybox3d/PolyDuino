#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget( new WarningPage( PolyboxModule::getInstance(this), this ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}
