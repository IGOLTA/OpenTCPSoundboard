#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QtMultimedia>

#include <QMainWindow>
#include <ui_mainwindow.h>

#include "ButtonSettingsWidget.h"

#define PORT 6587

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void generateButtonSettingsWidgets(char Width, char Height);

    Ui::MainWindow *ui;

    char width, height;
    QList<ButtonSettingsWidget*> buttonSettingsWidgets;

    QMediaPlayer* mediaPlayer = new QMediaPlayer;

private slots:
    void playMedia(const QString &path);
};

#endif
