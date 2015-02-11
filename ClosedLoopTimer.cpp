#include "ClosedLoopTimer.h"

ClosedLoopTimer::ClosedLoopTimer(QObject *parent) :
    QTimer(parent)
{
}


bool ClosedLoopTimer::startClosedLoop( int msec )
{
    this->setSingleShot( true );
    this->start( msec );
    int c=0;
    while ( this->isActive() )
    {
        qApp->processEvents();
    }
    return 0;
}


bool ClosedLoopTimer::startClosedLoop( int msec,  bool (*feedback_func)() )
{
    this->setSingleShot( true );
    this->start( msec );
    int c=0;
    while ( this->isActive() )
    {
        if ( (c=(*feedback_func)()) )
        {
            this->stop();
            return c;
        }
        qApp->processEvents();
    }
    return 0;
}
