#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QVector>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker();
signals:
    void newData(QVector<double> x, QVector<double> y);
    void finished();
public slots:
    void start();
    void stop();
private:
    bool run_ = false;
};

#endif // WORKER_H
