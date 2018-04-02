#ifndef FTIMER_H
#define FTIMER_H

#include "ftimer_global.h"
#include <QObject>
#include <QTimer>
#include <QThread>
#include <chrono>

class FTimer : public QObject
{
    Q_OBJECT

public:
    explicit FTimer(QObject *parent = nullptr);
    ~FTimer();

    void singleshot(long msec, const QObject *receiver, const char *member);

signals:

    void timeout();

private slots:

    void timerFinished();
    void counterFinished();

private:

    const QObject *m_receiver;
    const char *m_member;
    std::chrono::high_resolution_clock::time_point *m_timerStart;
    std::chrono::duration<double> *m_timerDuration;
    QThread *m_thread;
};

class Counter : public QObject{

    Q_OBJECT

public:

    explicit Counter(std::chrono::system_clock::time_point *timerStart, std::chrono::duration<double> *timerDuration);
    ~Counter();

signals:

    void countingFinished();

public slots:

    void startCounting();

private:

    std::chrono::system_clock::time_point *m_timerStart;
    std::chrono::duration<double> *m_timerDuration;
};

#endif // FTIMER_H
