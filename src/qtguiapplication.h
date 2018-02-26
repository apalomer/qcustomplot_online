#ifndef QTGUIAPPLICATION_H
#define QTGUIAPPLICATION_H

#include <QWidget>

#include <qcustomplot.h>

#include <thread>

namespace Ui {
class QtGuiApplication;
}

class QtGuiApplication : public QWidget
{
    Q_OBJECT

public:
    explicit QtGuiApplication(QWidget *parent = 0);
    ~QtGuiApplication();
private slots:
    void setPlotData(QVector<double> x,QVector<double> y);
    void pushButtonClicked();
signals:
    void newData(QVector<double> x, QVector<double> y);
private:
    Ui::QtGuiApplication *ui;
    QCustomPlot* plot_;
    std::thread thread_Displayer_;
    bool thread_run_flag_ = false;
    void thread_Displayer_fn();
};

#endif // QTGUIAPPLICATION_H
