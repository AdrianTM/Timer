#include <QtWidgets>

#include "timer.h"

Timer::Timer(QWidget *parent)
    : QLCDNumber(parent),
      running(false),
      timeout(new QTimer(this)),
      time(QTime(0, 0))
{
    connect(timeout, &QTimer::timeout, this, &Timer::processTimer);
    display(time.toString("hh:mm"));
}

void Timer::set(int min)
{
    time = QTime(0, 0);
    addMin(min + 1); // adds a minute to display done when 00:00
    display(time.addSecs(-60).toString("hh:mm"));
}

void Timer::addMin(int min)
{
    time = time.addSecs(min * 60);
}

void Timer::setColor(QPalette::ColorRole role, QColor color)
{
    QPalette palette = this->palette();
    palette.setBrush(role, color);
    setPalette(palette);
}

void Timer::subtractMin(int min)
{
    time = time.addSecs(-min * 60);
}

void Timer::start()
{
    timeout->start(1000);
    running = true;
}

void Timer::stop()
{
    timeout->stop();
    running = false;
}

QTime Timer::getTime()
{
    return time;
}

void Timer::processTimer()
{
    if (running) {
        time = time.addSecs(-1);
        QString text = time.toString("hh:mm");
        if ((time.second() % 2) != 0) {
            text[2] = ' ';
        }
        display(text);

        if (time == QTime(0, 1)) { // added a minute to time to end clock on 00:00
            display("00:00");
            processDone();
        }
    }
}

void Timer::processDone()
{
    stop();
    QMessageBox::information(this, tr("Done"), "<h1>" + tr("Time's up!") + "</h1>");
}


