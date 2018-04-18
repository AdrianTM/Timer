#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QAbstractButton>
#include <QMouseEvent>

#include "timer.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    void apply();
    void loadSettings();
    void pickColor(QWidget *widget);
    void setColor(QWidget *widget, QColor color);

signals:
    void changed();

public slots:
    void show();

protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_pushReset_clicked();
    void on_cb_no_toolbar_clicked(bool checked);


private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
