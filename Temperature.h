#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <QObject>
#include <QString>
/**
 * @brief The Mode enum Degree unit, Celcius ? Kelvin ? Banana ? Pony ? ....
 */
enum Mode{
    Celcius, Kelvin
};


/**
 * @brief The Temperature class Provide a Class to store Temperature data and utilities functions. Can retrveive a  -ready-to-printer String (value+DegreeUnit) or just the value.
 */
class Temperature
{
public:
#define DEFAULT_TEMP_VALUE -42.42
#define EPSYLON 0.01
    explicit Temperature();
    explicit Temperature(float temp);
    /**
     * @brief getValue Current stored temperature as a float.
     * @return temperature as float
     */
    float getValue() const;

    void setValue(float temp);

    void setState( bool state);

    QString str();

    /**
     * @brief isDefault Return True if the current stored value is the default value. Usefull, for example, to know if a captor is working or no.
     * @return
     */
    bool isDefault() const;


private:
    float _value;
    Mode _mode;

};

#endif // TEMPERATURE_H
