#ifndef BUTTONSETTINGSWIDGET_H
#define BUTTONSETTINGSWIDGET_H

#include <QtWidgets>

class ButtonSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonSettingsWidget(QWidget* parent = nullptr);

    QString getPath();

private:
    QGridLayout* layout = new QGridLayout(this);

    QLabel* browseLabel = new QLabel(this);
    QLineEdit* browseLineEdit = new QLineEdit(this);
    QPushButton* browseButton = new QPushButton(this);

    QPushButton* audioTestButton = new QPushButton(this);

    QSpacerItem* spacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding);

private slots:
    void browse();
    void testAudioSlot();

signals:
    void testAudio(QString path);
};

#endif // BUTTONSETTINGSWIDGET_H
