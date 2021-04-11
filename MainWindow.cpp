#include "MainWindow.h"

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

    loadSavedData();
}

MainWindow::~MainWindow()
{
    saveData();
}

void MainWindow::loadSavedData() {
    if(dataFile->open(QIODevice::ReadOnly))
    {
        while(!dataFile->atEnd()) {
            QString line = dataFile->readLine();
            line.chop(1);
            if(line.startsWith("button_path: ")) {
                line.replace("button_path: ", "");

                QString coords = line;
                coords.left(2);

                buttonsAudioPaths.insert(coords.toUInt(), line.remove(0, 2));
            } else if(line.startsWith("audio_device: ")) {
                int i = ui->outputDeviceComboBox->findText(line.replace("audio_device: ", ""));
                if(i != -1) ui->outputDeviceComboBox->setCurrentIndex(i);
            }
            else if(line.startsWith("audio_volume: "))
                ui->volumeSlider->setValue(line.replace("audio_volume: ", "").toInt());
            else if(line.startsWith("ip: "))
                ui->ipLineEdit->setText(line.replace("ip: ", ""));
        }

        dataFile->close();
    }
}

void MainWindow::saveData() {
    if(dataFile->open(QIODevice::WriteOnly))
    {
        QString text;
        if(buttonSettingsWidgets.size() > 0){
            for(int i = 0; i < getButtonsWidth(); i++) {
                for(int j = 0; j < getButtonsHeight(); j++) {
                    text.append("button_path: ");
                    QString coords = QString::number((i << 4) | j, 16);
                    if(coords.size() == 1) coords = "0" + coords;
                    text.append(coords);
                    text.append(buttonSettingsWidgets[i * getButtonsHeight() + j]->getPath());
                    text.append("\n");
                }
            }
        }


        text.append("audio_device: ");
        text.append(ui->outputDeviceComboBox->currentText());
        text.append("\n");

        text.append("audio_volume: ");
        text.append(QString::number(ui->volumeSlider->value()));
        text.append("\n");


        text.append("ip: ");
        text.append(ui->ipLineEdit->text());
        text.append("\n");

        dataFile->write(text.toUtf8().constData(), text.toUtf8().size());
    }

    dataFile->close();
}

void MainWindow::playAudioSample(const unsigned char &pos) {
    unsigned char x = (pos & 0xF0) >> 4;
    unsigned char y = pos & 0x0F;
    playMedia(buttonSettingsWidgets[x * (getButtonsHeight() - 1) + y]->getPath());
}

void MainWindow::initConnection() {
    soundboardSocket = new SoundboardSocket(ui->ipLineEdit->text(), PORT, 3000, this);

    connect(
                soundboardSocket,
                SIGNAL(ready(unsigned char)),
                this,
                SLOT(generateButtonSettingsWidgets(unsigned char))
    );

    connect(
                soundboardSocket,
                SIGNAL(buttonPressed(unsigned char)),
                this,
                SLOT(playAudioSample(unsigned char))
    );

    connect(
                soundboardSocket,
                SIGNAL(connectionClosed()),
                this,
                SLOT(connectionClosed())
    );

    soundboardSocket->start();
}

void MainWindow::connectionClosed() {
    ui->connectionStatus->setText("Disconected");
}

void MainWindow::generateButtonSettingsWidgets(const unsigned char &Dimensions)
{
    ui->connectionStatus->setText("Connected");

    buttonsDimensions = Dimensions;

    QGridLayout* gridLayout = new QGridLayout(ui->buttonsTab);
    gridLayout->setMargin(0);
    ui->buttonsTab->setLayout(gridLayout);

    for(unsigned char i = 0; i < getButtonsWidth(); i++) {
        for(unsigned char j = 0; j < getButtonsHeight(); j++) {
            buttonSettingsWidgets.push_back(new ButtonSettingsWidget(this));
            gridLayout->addWidget(buttonSettingsWidgets[i * getButtonsHeight() + j], i, j);

            if(buttonsAudioPaths.contains((i << 4) | j))
                buttonSettingsWidgets[i * getButtonsHeight() + j]->setPath(buttonsAudioPaths[(i << 4) | j]);

            connect(buttonSettingsWidgets[i * getButtonsHeight() + j], SIGNAL(testAudio(QString)), this, SLOT(playMedia(QString)));
        }
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
