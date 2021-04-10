#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QAudioDeviceInfo> deviceInfos = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);

    for (const QAudioDeviceInfo &deviceInfo : deviceInfos)
    {
        audioDevicesFromName.insert(deviceInfo.deviceName(), deviceInfo);
        ui->outputDeviceComboBox->addItem(deviceInfo.deviceName());
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::generateButtonSettingsWidgets(char Width, char Height)
{
    width = Width; height = Height;

    QGridLayout* gridLayout = new QGridLayout(ui->buttonsTab);
    ui->buttonsTab->setLayout(gridLayout);

    for(int i = 0; i < width * height; i++) {
        buttonSettingsWidgets.push_back(new ButtonSettingsWidget(this));
        gridLayout->addWidget(buttonSettingsWidgets[i], i % height, i / height);

        connect(buttonSettingsWidgets[i], SIGNAL(testAudio(QString)), this, SLOT(playMedia(QString)));
    }
}

void MainWindow::playMedia(const QString &path)
{
    QAudioDeviceInfo deviceInfo = audioDevicesFromName[ui->outputDeviceComboBox->currentText()];
    QAudioFormat format = deviceInfo.preferredFormat();
    QAudioOutput* audioOutput = new QAudioOutput(audioDevicesFromName[ui->outputDeviceComboBox->currentText()], audioDevicesFromName[ui->outputDeviceComboBox->currentText()].preferredFormat(), this);
    audioOutput->setVolume(ui->volumeSlider->value());

    audioFileStream = new AudioFileStream;
    if(!audioFileStream->init(format))
        return;

    audioOutput->start(audioFileStream);
    audioFileStream->play(path);
}
