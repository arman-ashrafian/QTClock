#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

int timer = 0; // Event Timer

/* Timer */
int timerMin = 0;
int timerSec = 0;
bool timerRunning = false;

/* Stopwatch */
int stopWatchMin = 0;
int stopWatchSec = 0;
bool stopWatchRunning = false;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = startTimer(1000);

    MainWindow::setMinimumHeight(1000);
    MainWindow::setMinimumWidth(1000);

    ui->timerMins->setMinimum(0); // set timerMins minimum = 0
    ui->timerSecs->setMinimum(0); // set timerSecs minimum = 0

    ui->stopwatch->display("0:00"); // set stopwatch to 0:00
}


MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getTime()
{
    ostringstream ss;
    time_t now = time(0);
    tm *lt = localtime(&now); // local time

    int hour = lt->tm_hour;
    int min = lt->tm_min;

    if(hour > 12) {
        hour -= 12;
    }

    if(min < 10) {
        ss << hour << ":0" << min;

    }
    else {
        ss << hour << ":" << min;
    }

    return QString::fromStdString(ss.str());
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    QString time;
    QString timerTime;
    QString stopwatchTime;
    event->accept();

    time = getTime();
    ui->clock->display(time);

    timerTime = getTimerTime();
    ui->timer->display(timerTime);

    stopwatchTime = getStopwatchTime();
    ui->stopwatch->display(stopwatchTime);

    if(timerRunning) {
        /* check if any time left */
        if(timerMin == 0 && timerSec == 0) {timerRunning = false;}

        else {
            /* decrease time */
            if(timerSec > 0)
                timerSec--;
            else {
                timerSec = 59;
                timerMin--;
            }
        }
    }



    if(stopWatchRunning) {
        if(stopWatchSec < 59) {
            stopWatchSec++;
        }
        else {
            stopWatchSec = 0;
            stopWatchMin++;
        }
    }
}


void MainWindow::on_timerMins_editingFinished()
{
     timerMin = ui->timerMins->value();
}



void MainWindow::on_timerSecs_editingFinished()
{
    timerSec = ui->timerSecs->value();
}

QString MainWindow::getTimerTime()
{
    ostringstream ss;

    ss << timerMin << ":";

    if(timerSec < 10)
        ss << "0" << timerSec;
    else
        ss << timerSec;

    return QString::fromStdString(ss.str());
}

QString MainWindow::getStopwatchTime()
{
    ostringstream ss;

    ss << stopWatchMin << ":";

    if(stopWatchSec < 10)
        ss << "0" << stopWatchSec;
    else
        ss << stopWatchSec;

    return QString::fromStdString(ss.str());
}


void MainWindow::on_startTimer_clicked()
{
    timerRunning = !timerRunning;
}

void MainWindow::on_stopwatchStart_clicked()
{
    stopWatchRunning = !stopWatchRunning;
}

void MainWindow::on_stopwatchReset_clicked()
{
    stopWatchMin = 0;
    stopWatchSec = 0;
}


void MainWindow::on_timerReset_clicked()
{
    timerMin = 0;
    timerSec = 0;
}
