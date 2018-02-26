#include "qtguiapplication.h"
#include "ui_qtguiapplication.h"
#include <unistd.h>

double fRand(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

QtGuiApplication::QtGuiApplication(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtGuiApplication)
{
    // Set up UI
    ui->setupUi(this);
    plot_ = ui->qcustomplot;

    // Register data type for signals
    qRegisterMetaType<QVector<double>>("QVector<double>");

    // Prepare graph
    plot_->addGraph();

    // Connect
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(pushButtonClicked()));
    connect(this,SIGNAL(newData(QVector<double>,QVector<double>)),this,SLOT(setPlotData(QVector<double>,QVector<double>)));
}

QtGuiApplication::~QtGuiApplication()
{
    delete ui;
}

void QtGuiApplication::pushButtonClicked()
{
    if (thread_run_flag_)
    {
        ui->pushButton->setText("Display");
        thread_run_flag_ = false;
        if (thread_Displayer_.joinable())
        {
            thread_Displayer_.join();
        }
    }
    else
    {
        thread_run_flag_ = false;
        if (thread_Displayer_.joinable())
        {
            thread_Displayer_.join();
        }
        ui->pushButton->setText("Stop");
        thread_run_flag_ = true;
        thread_Displayer_ = std::thread(&QtGuiApplication::thread_Displayer_fn,
          this);
    }
}

void QtGuiApplication::setPlotData(QVector<double> x, QVector<double> y)
{
    plot_->graph(0)->setData(x, y);
    plot_->rescaleAxes();
    plot_->replot();
}

void QtGuiApplication::thread_Displayer_fn()
{
    while (thread_run_flag_)
    {
        QVector<double> x(ui->spinBox->value()), y(ui->spinBox->value());
        for (int i = 0; i<ui->spinBox->value(); ++i)
        {
            x[i] = i;
            y[i] = fRand(0,10);
        }
        emit newData(x,y);
        usleep(ui->doubleSpinBox->value()*1000);// convert to us
    }
}
