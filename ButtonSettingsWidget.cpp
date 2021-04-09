#include "ButtonSettingsWidget.h"

ButtonSettingsWidget::ButtonSettingsWidget(QWidget* parent) : QWidget(parent)
{
    layout->addWidget(browseLabel, 0, 0);
    layout->addWidget(browseLineEdit, 0, 1);
    layout->addWidget(browseButton, 0, 2);

    layout->addWidget(audioTestButton, 1, 2);

    layout->addItem(spacer, 2, 1);

    browseLabel->setText(tr("Select an audio sample"));
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

void ButtonSettingsWidget::testAudioSlot()
{
    testAudio(getPath());
}
