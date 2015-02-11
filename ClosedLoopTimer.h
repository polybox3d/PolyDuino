#ifndef CLOSEDLOOPTIMER_H
#define CLOSEDLOOPTIMER_H

#include <QApplication>
#include <QTimer>

class ClosedLoopTimer : public QTimer
{
    Q_OBJECT
public:
    explicit ClosedLoopTimer(QObject *parent = 0);
    /** return 0 or feedback return value**/
    bool startClosedLoop(int msec);
    bool startClosedLoop(int msec, bool (*feedback_func)() );

signals:

public slots:

};

#endif // CLOSEDLOOPTIMER_H
