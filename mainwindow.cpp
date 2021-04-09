#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    generateButtonSettingsWidgets(2, 5);

    QAction* audioOutAction = ui->actionAudio_output;
    QList<QAudioDeviceInfo> deviceInfos = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);

    for (QAudioDeviceInfo &deviceInfo : deviceInfos)
    {
        QAction* action(this);
        action->setText(deviceInfo.deviceName());
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::generateButtonSettingsWidgets(char Width, char Height)
{
    width = Width; height = Height;

    for(int i = 0; i < width * height; i++) {
        buttonSettingsWidgets.push_back(new ButtonSettingsWidget(this));
        ui->gridLayout->addWidget(buttonSettingsWidgets[i], i % height, i / height);

        connect(buttonSettingsWidgets[i], SIGNAL(testAudio(QString)), this, SLOT(playMedia(QString)));
    }
}

void MainWindow::playMedia(const QString &path)
{
    qInfo() << path;
    mediaPlayer->setMedia(QUrl::fromLocalFile(path));

    mediaPlayer->play();
}
