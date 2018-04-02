#include "ftimer.h"

Counter::Counter(std::chrono::system_clock::time_point *timerStart, std::chrono::duration<double> *timerDuration)
{

    m_timerStart = timerStart;
    m_timerDuration = timerDuration;
}

Counter::~Counter()
{

    m_timerStart = NULL;
    m_timerDuration = NULL;
}

void Counter::startCounting()
{

    while(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - *m_timerStart) != *m_timerDuration){

        if(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - *m_timerStart) == *m_timerDuration){

            emit countingFinished();
            return;
        }
    }
}

FTimer::FTimer(QObject *parent) : QObject(parent)
{

    m_timerDuration = new std::chrono::duration<double>;
    m_timerStart = new std::chrono::high_resolution_clock::time_point;
    m_thread = new QThread(this);
}

FTimer::~FTimer()
{

    delete m_timerDuration;
    delete m_timerStart;

    m_timerDuration = NULL;
    m_timerStart = NULL;
    m_receiver = NULL;
    m_member = NULL;
}

void FTimer::singleshot(long msec, const QObject *receiver, const char *member)
{

    *m_timerStart = std::chrono::high_resolution_clock::now();
    m_receiver = receiver;
    m_member = member;
    *m_timerDuration = std::chrono::duration_cast<std::chrono::duration<double>> ((std::chrono::milliseconds)(msec));

    if(msec > 2){

        QTimer::singleShot(msec - 1, Qt::PreciseTimer, m_receiver, member);
    }
}

void FTimer::timerFinished()
{

    Counter *c = new Counter(m_timerStart, m_timerDuration);
    c->moveToThread(m_thread);
    connect(m_thread, SIGNAL(finished()), c, SLOT(deleteLater()));
    connect(m_thread, SIGNAL(started()), c, SLOT(startCounting()));
    connect(c, SIGNAL(countingFinished()), this, SLOT(counterFinished()));
    m_thread->start();
}

void FTimer::counterFinished()
{

    connect(this, SIGNAL(counterFinished()), m_receiver, m_member);
    emit counterFinished();
}
