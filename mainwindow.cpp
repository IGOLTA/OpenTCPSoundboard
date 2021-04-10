#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(initConnection()));

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

void MainWindow::playAudioSample(const unsigned char &pos) {
    unsigned char x = (pos & 0xF0) >> 4;
    unsigned char y = pos & 0x0F;
    playMedia(buttonSettingsWidgets[x * getButtonsHeight() + y]->getPath());
}

void MainWindow::initConnection() {
    soundboardSocket = new SoundboardSocket(ui->ipLineEdit->text(), PORT, 3000, this);

    connect(
                soundboardSocket,
                SIGNAL(ready(unsigned char)),
                this,
                SLOT(generateButtonSettingsWidgets(unsigned char))
    );

    soundboardSocket->start();
}

void MainWindow::generateButtonSettingsWidgets(const unsigned char &Dimensions)
{
    buttonsDimensions = Dimensions;

    QGridLayout* gridLayout = new QGridLayout(ui->buttonsTab);
    ui->buttonsTab->setLayout(gridLayout);

    unsigned char height = getButtonsHeight();
    for(int i = 0; i < getButtonsWidth() * height; i++) {
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
