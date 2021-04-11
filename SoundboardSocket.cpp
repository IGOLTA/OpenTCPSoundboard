#include "SoundboardSocket.h"

SoundboardSocket::SoundboardSocket(QString IP, short Port, int Timeout, QObject *parent) :
    QObject(parent), ip(IP), port(Port), timeout(Timeout)
{
    socket = new QTcpSocket(this);
}

void SoundboardSocket::start() {
    socket->connectToHost(ip, port);

    if(socket->waitForConnected(timeout)) {
        char dims = 0x00;

        socket->write(&SIZE_REQUEST_BYTE, 1);
        if(socket->waitForReadyRead(timeout)) {
            socket->read(&dims, 1);
            emit ready(dims);

            connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
        }else {
            emit connectionClosed();
            socket->close();
            return;
        }
    }else {
        emit connectionClosed();
        socket->close();
        return;
    }
}

void SoundboardSocket::socketReadyRead() {
    QByteArray bytes = socket->readAll();
    for(int i = 0; i < bytes.size(); i++) {
        emit buttonPressed(bytes.at(i));
    }
}
