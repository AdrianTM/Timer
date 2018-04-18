#ifndef TIMER_H
#define TIMER_H

#include <QLCDNumber>
#include <QTime>

class Timer : public QLCDNumber
{
    Q_OBJECT

public:
    Timer(QWidget *parent = 0);

    bool running;

    void set(int min);
    void addMin(int min);
    void setColor(QPalette::ColorRole role, QColor color);
    void subtractMin(int min);
    void start();
    void stop();
    QTime getTime();

private slots:
    void processTimer();
    void processDone();

private:
    QTimer *timeout;
    QTime time;

};

#endif
