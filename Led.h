#ifndef LED_H
#define LED_H

#include <QLabel>

#define DEFAULT_LED_SIZE 20
/**
 * @brief The Led class Constructs a basic Led elements, using a QLabel component.
 * The led can be set to on or off, or just toggle. The size can be adjusted freely, the image/icon will scale.
 *
 * @todo : add optionnal setup for non-important content, and different image (for example, led off using a led-gren-off instead of red)
 */
class Led : public QLabel
{
    Q_OBJECT
public:
    /**
     * @brief Led Constructs a basic Led elements, using a QLabel as base with a parent
     * @param parent
     */
    explicit Led(QWidget *parent = 0);
    /**
     * @brief Led Constructs a basic Led elements, using a QLabel as base with a parent.
     * @param activated is the led on or off ?
     * @param parent QWidget parent
     */
    Led(bool activated, QWidget *parent);

signals:

public slots:
    /**
     * @brief updateLed Repaints graphical component.
     */
    void updateLed();
    /**
     * @brief off Set the led OFF, and repaints the Widget.
     */
    void off();
    /**
     * @brief on Set the led ON, and repaints the Widget.
     */
    void on();
    /**
     * @brief toggle Set the led On if the current state is Off, and OFF if the current state is ON. Swap.
     */
    void toggle();
    /**
     * @brief setActivated Set the current state of the Led. True for ON and False for OFF.
     * @param activated
     */
    void setActivated( bool activated );
    /**
     * @brief setSize setup the size of the LED. The image/icon auto-scales with the size given
     * @param w width of the LED.
     * @param h height of the LED.
     */
    void setSize( int w, int h );

private:
    void init();

    bool _activated;


};

#endif // LED_H
