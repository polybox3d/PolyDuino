#ifndef HOMEBUTTON_H
#define HOMEBUTTON_H

#include <QPushButton>
#include "PolyboxModule.h"

/**
 * @brief The HomeButton class Cosntruct the Home button using the logo. Th size can be updated.
 */
class HomeButton : public QPushButton
{
    Q_OBJECT
public:
    explicit HomeButton(QWidget *parent = 0);
    HomeButton(int w, int h, QWidget *parent);
    void setSize( int w, int h);


signals:

public slots:
    void changeIcon(QPixmap img);
    void changeIconOnConnectorType(PolyboxModule::ConnectorType type);

};

#endif // HOMEBUTTON_H
