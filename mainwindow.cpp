#include <QSettings>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QStringList args, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    help(new Help(this)),
    timer(new Timer(this)),
    setui(new Settings(this))
{
    ui->setupUi(this);
    setWindowTitle(tr("Timer"));

    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags | Qt::WindowStaysOnTopHint);
    resize(200, 120);

    ui->gridLayout->addWidget(timer, 1, 0, 1, -1);
    ui->statusbar->hide();

    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
    settings.setValue("geometry-session", saveGeometry());

    connect(ui->actionAbout_Timer, &QAction::triggered, help, &Help::show);
    connect(ui->actionSettings, &QAction::triggered, setui, &Settings::show);
    connect(ui->actionStart, &QAction::triggered, this, &MainWindow::on_pushStart_pressed);
    connect(ui->actionToggle, &QAction::triggered, this, &MainWindow::on_pushToggle_pressed);
    connect(ui->actionToggleToolbar, &QAction::triggered, this, &MainWindow::toggleToolBar);
    connect(setui, &Settings::changed, this, &MainWindow::loadSettings);

    loadSettings();
    processArgs(args);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toggleMaximize()
{
    windowState() == Qt::WindowMaximized ? showNormal() : showMaximized();
}

void MainWindow::toggleFullScreen()
{
    isFullScreen() ? showNormal() : showFullScreen();
}

void MainWindow::showHelp()
{
    help->show();
}

void MainWindow::showToolBar(bool show)
{
    ui->spinMinutes->setVisible(show);
    ui->label->setVisible(show);
    ui->pushStart->setVisible(show);
    ui->pushToggle->setVisible(show);
    if (ui->label->isVisible()) {
        ui->actionToggleToolbar->setText("Hide &Toolbar");
    } else {
        ui->actionToggleToolbar->setText("Show &Toolbar");
    }
}

void MainWindow::toggleToolBar()
{
    showToolBar(!ui->label->isVisible());
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        ui->menubar->setVisible(!ui->label->isVisible());
        showToolBar(ui->menubar->isVisible());
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case (Qt::Key_F):
        toggleMaximize();
        break;
    case (Qt::Key_F1):
        showHelp();
        break;
    case (Qt::Key_F9):
        toggleToolBar();
        break;
    case (Qt::Key_F10):
        ui->menubar->setVisible(!ui->menubar->isVisible());
        break;
    case (Qt::Key_F11):
        toggleFullScreen();
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->modifiers()&Qt::AltModifier) {
        multi_keys = true;
    } else if (event->key() == Qt::Key_Alt && !multi_keys){
        ui->menubar->isVisible() ? ui->menubar->hide() : ui->menubar->show();
    } else if (event->key() == Qt::Key_Alt) {
        multi_keys = false; // reset
    }
}


void MainWindow::on_pushStart_pressed()
{
    timer->set(ui->spinMinutes->value());
    timer->start();
    ui->pushToggle->setText("Sto&p");
}

void MainWindow::on_pushToggle_pressed()
{
    if (ui->pushToggle->text() == tr("Sto&p")) {
        if (timer->running) {
            timer->stop();
            ui->actionToggle->setText("&Resume");
            ui->pushToggle->setText("&Resume");
        }
    } else {
        timer->start();
        ui->actionToggle->setText("&Stop");
        ui->pushToggle->setText("Sto&p");
    }
}

void MainWindow::closeEvent(QCloseEvent *)
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
}

void MainWindow::loadSettings()
{
    QSettings settings;

    QColor fgColor = settings.value("fgColor", this->palette().color(QPalette::WindowText)).value<QColor>();
    timer->setColor(QPalette::WindowText, fgColor);

    bool autorun = settings.value("autorun", false).toBool();
    bool no_menu = settings.value("nomenu", false).toBool();
    bool no_toolbar = settings.value("notoolbar", false).toBool();
    int default_time = settings.value("default_time", 15).toInt();
    ui->menubar->setHidden(no_menu);
    ui->spinMinutes->setValue(default_time);
    if (autorun) {
        timer->set(default_time);
        timer->start();
    }
    showToolBar(!no_toolbar);
    if (no_toolbar) {
        ui->actionToggleToolbar->setText("Show &Toolbar");
    } else {
        ui->actionToggleToolbar->setText("Hide &Toolbar");
    }
}

void MainWindow::processArgs(QStringList args)
{
    for (QString arg : args) {
        if (arg.contains("--t=")) {
            qDebug() << tr("Wrong syntax, use either -t=xxx or --timer=xxx");
            break;
        }
        if (arg.contains("-t=") || arg.contains("--timer=")) {
            QString min = arg.remove("-t=").remove("--timer=");
            timer->set(min.toInt());
            timer->start();
        }
    }

    if (args.contains("-n") || args.contains("--no-toolbar")) {
        ui->menubar->hide();
        showToolBar(false);
    }
    if (args.contains("-m") || args.contains("--maximized")) {
        toggleMaximize();
    }
    if (args.contains("-f") || args.contains("--full-screen")) {
        toggleFullScreen();
    }
}
