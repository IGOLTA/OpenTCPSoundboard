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

    unsigned short getButtonsWidth() { return ((buttonsDimensions & 0xF0) >> 4) + 1; }
    unsigned short getButtonsHeight() { return (buttonsDimensions & 0x0F) + 1; }

public slots:
    void playAudioSample(const unsigned char &pos);

private:
    Ui::MainWindow *ui;

    QMap<unsigned char, QString> buttonsAudioPaths;
    unsigned char buttonsDimensions;
    QList<ButtonSettingsWidget*> buttonSettingsWidgets;

    QMap<QString, QAudioDeviceInfo> audioDevicesFromName;

    AudioFileStream* audioFileStream;
    SoundboardSocket* soundboardSocket;

    QFile* dataFile = new QFile("data", this);


    void loadSavedData();
    void saveData();
private slots:
    void playMedia(const QString &path);
    void initConnection();
    void generateButtonSettingsWidgets(const unsigned char &Dimensionss);
    void connectionClosed();
};

#endif
