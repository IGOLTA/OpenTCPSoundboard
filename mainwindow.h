#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMap>
#include <QtMultimedia>

#include <QMainWindow>
#include <ui_mainwindow.h>

#include "ButtonSettingsWidget.h"
#include "AudioFileStream.h"
#include "SoundboardSocket.h"

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

    unsigned char getButtonsWidth() { return (buttonsDimensions & 0xF0) >> 4; }
    unsigned char getButtonsHeight() { return buttonsDimensions & 0x0F; }

public slots:
    void playAudioSample(const unsigned char &pos);

private:
    Ui::MainWindow *ui;

    unsigned char buttonsDimensions;
    QList<ButtonSettingsWidget*> buttonSettingsWidgets;

    QMap<QString, QAudioDeviceInfo> audioDevicesFromName;

    AudioFileStream* audioFileStream;
    SoundboardSocket* soundboardSocket;

private slots:
    void playMedia(const QString &path);
    void initConnection();
    void generateButtonSettingsWidgets(const unsigned char &Dimensionss);
};

#endif
