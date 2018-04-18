#include <QColorDialog>
#include <QSettings>
#include <QDebug>

#include "settings.h"
#include "ui_settings.h"


Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->adjustSize();

    QSettings settings;
    QColor fgColor = settings.value("fgColor", this->palette().color(QPalette::WindowText)).value<QColor>();
    ui->fgColor->setPalette(QPalette(fgColor));

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Settings::apply);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::apply()
{
    QSettings settings;
    settings.setValue("autorun", ui->cb_autostart->isChecked());
    settings.setValue("nomenu", ui->cb_no_menu->isChecked());
    settings.setValue("notoolbar", ui->cb_no_toolbar->isChecked());
    settings.setValue("default_time", ui->spinDefault->value());

    if(ui->radioReset->isChecked()) {
        parentWidget()->showNormal();
    } else if (ui->radioMaximize->isChecked()) {
        parentWidget()->showMaximized();
    } else if (ui->radioFull->isChecked()) {
        parentWidget()->showFullScreen();
    }

    emit changed();
}

void Settings::loadSettings()
{
    QSettings settings;
    bool autorun = settings.value("autorun", false).toBool();
    bool no_menu = settings.value("nomenu", false).toBool();
    bool no_toolbar = settings.value("notoolbar", false).toBool();
    int default_time = settings.value("default_time", 15).toInt();
    ui->cb_autostart->setChecked(autorun);
    ui->cb_no_menu->setChecked(no_menu);
    ui->cb_no_toolbar->setChecked(no_toolbar);
    ui->spinDefault->setValue(default_time);
}

void Settings::pickColor(QWidget *widget)
{
    Qt::WindowFlags flags = this->windowFlags();
    Qt::WindowFlags flags_parent = this->parentWidget()->windowFlags();
    this->setWindowFlags(flags | Qt::WindowStaysOnBottomHint);
    this->parentWidget()->setWindowFlags(flags_parent | Qt::WindowStaysOnBottomHint);

    QColorDialog *dialog = new QColorDialog(this);

    QColor color = dialog->getColor(widget->palette().color(QWidget::backgroundRole()));
    if (color.isValid()) {
        setColor(widget, color);
    }

    this->setWindowFlags(flags | Qt::WindowStaysOnTopHint);
    this->parentWidget()->setWindowFlags(flags_parent | Qt::WindowStaysOnTopHint);
    this->parentWidget()->show();
    this->show();
}

void Settings::setColor(QWidget *widget, QColor color)
{
    QSettings settings;
    widget->parentWidget()->show();
    if (color.isValid()) {
        QPalette pal = palette();
        pal.setColor(QPalette::Window, color);
        widget->setAutoFillBackground(true);
        widget->setPalette(pal);
    }
    settings.setValue(widget->objectName(), color);
}

void Settings::show()
{
   loadSettings();
   QWidget::show();
}

void Settings::mousePressEvent(QMouseEvent *event)
{
     if (event->button() == Qt::LeftButton) {
        if(ui->fgColor->underMouse()) {
            pickColor(ui->fgColor);
        }
     }
}

void Settings::on_pushReset_clicked()
{
    ui->cb_autostart->setChecked(false);
    ui->cb_no_menu->setChecked(false);
    ui->cb_no_toolbar->setChecked(false);
    ui->radioReset->setChecked(true);
    ui->spinDefault->setValue(15);
    setColor(ui->fgColor, this->palette().color(QPalette::WindowText));
}

void Settings::on_cb_no_toolbar_clicked(bool checked)
{
    if (checked) {
        ui->cb_autostart->setChecked(true);
    }
}

