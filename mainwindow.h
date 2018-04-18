#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

#include <timer.h>
#include <help.h>
#include <settings.h>

class help;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QStringList args, QWidget *parent = 0);
    ~MainWindow();

    void showHelp();
    void showToolBar(bool show);
    void toggleToolBar();
    void toggleMaximize();
    void toggleFullScreen();

protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void closeEvent(QCloseEvent *);
    void loadSettings();
    void on_pushStart_pressed();
    void on_pushToggle_pressed();

private:
    Ui::MainWindow *ui;

    bool multi_keys;
    Help *help;
    Timer *timer;
    Settings *setui;
    void processArgs(QStringList args);
};

#endif // MAINWINDOW_H
