#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimerEvent>
#include <ctime>
#include <sstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString getTime();
    QString getTimerTime();
    QString getStopwatchTime();
    void timerEvent(QTimerEvent *event);

private slots:
    void on_timerMins_editingFinished();

    void on_timerSecs_editingFinished();

    void on_startTimer_clicked();

    void on_stopwatchStart_clicked();

    void on_stopwatchReset_clicked();

    void on_timerReset_clicked();

private:
    Ui::MainWindow *ui;

    int timer;
};

#endif // MAINWINDOW_H
