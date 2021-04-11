#ifndef SOUNDBOARDSOCKET_H
#define SOUNDBOARDSOCKET_H

#include <QObject>
#include <QTcpSocket>

class SoundboardSocket : public QObject
{
    Q_OBJECT
public:
    explicit SoundboardSocket(QString IP, short Port, int Timeout = 3000, QObject *parent = nullptr);

    QString getIp() { return ip; }

    void start();

private:
    const char SIZE_REQUEST_BYTE = 0xDA;

    QString ip;
    short port;
    int timeout;
    QTcpSocket* socket;

private slots:
    void socketReadyRead();

signals:
    void ready(const unsigned char &Dimensions);
    void connectionClosed();
    void buttonPressed(unsigned char Position);
};

#endif // SOUNDBOARDSOCKET_H
