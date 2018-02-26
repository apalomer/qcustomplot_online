#include "worker.h"
#include <QApplication>
#include <QVector>
#include <QDebug>
#include <unistd.h>

double fRand(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

Worker::Worker()
{
    connect(this,SIGNAL(finished()),this,SLOT(deleteLater()));
}

void Worker::start()
{
    run_ = true;
    int sz(16384);
    while (run_)
    {
        QVector<double> x(sz), y(sz);
        for (int i = 0; i<sz; ++i)
        {
            x[i] = i;
            y[i] = fRand(0,10);
        }
        emit newData(x,y);
        QApplication::processEvents();
        usleep(100000);
    }
    emit finished();
}

void Worker::stop()
{
    run_ = false;
}
