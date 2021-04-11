#include "ButtonSettingsWidget.h"

ButtonSettingsWidget::ButtonSettingsWidget(QWidget* parent) : QWidget(parent)
{
    layout->addWidget(browseLineEdit, 0, 0);
    layout->addWidget(browseButton, 0, 1);

    layout->addWidget(audioTestButton, 1, 1);

    layout->addItem(spacer, 2, 1);

    browseButton->setText(tr("Browse..."));

    audioTestButton->setText(tr("Test audio sample"));

    connect(browseButton, SIGNAL(clicked()), this, SLOT(browse()));
    connect(audioTestButton, SIGNAL(clicked()), this, SLOT(testAudioSlot()));
}

void ButtonSettingsWidget::browse()
{
    browseLineEdit->setText(QFileDialog::getOpenFileName(this, tr("Open Sample..."), "", tr("Audio Filea (*.wav *.mid *.midi *.aiff *.aac *.mp3 *.mp4)")));
}

QString ButtonSettingsWidget::getPath()
{
    return browseLineEdit->text();
}

void ButtonSettingsWidget::setPath(QString path)
{
    browseLineEdit->setText(path);
}

void ButtonSettingsWidget::testAudioSlot()
{
    testAudio(getPath());
}
