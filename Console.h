#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>

#include "PolyboxModule.h"

namespace Ui {
class Console;
}

class Console : public QWidget
{
    Q_OBJECT

public:
    explicit Console(QWidget *parent = 0);
    ~Console();
public slots:
    void parseData();
private slots:
    void on_sendCodeButton_clicked();

    void on_inputCode_returnPressed();

private:
    Ui::Console *ui;
};

#endif // CONSOLE_H
