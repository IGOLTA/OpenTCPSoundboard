#ifndef SOUNDBOARDSOCKET_H
#define SOUNDBOARDSOCKET_H

#include <QObject>

class SoundboardSocket : public QObject
{
    Q_OBJECT
public:
    explicit SoundboardSocket(QObject *parent = nullptr);

signals:

};

#endif // SOUNDBOARDSOCKET_H
