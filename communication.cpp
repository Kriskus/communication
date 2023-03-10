#include "communication.h"

Communication::Communication(const QString &hostName, quint16 port)
    : socket_(new QTcpSocket)
    , sync_(new QMutex)
{
    connectToHost(hostName, port);
    connect(socket_, &QTcpSocket::readyRead, this, &Communication::readFromHost);
}

Communication::~Communication()
{
    disconnectFromHost();
    delete socket_;
    delete sync_;
}

void Communication::connectToHost(const QString &hostName, quint16 port)
{
    socket_->connectToHost(hostName, port);
}

void Communication::disconnectFromHost()
{
    socket_->disconnectFromHost();
}

void Communication::writeToHost(const QByteArray &data)
{
    emit pause();
    sync_->lock();
    socket_->write(data);
    socket_->waitForBytesWritten(-1);
    emit sendWritedData(data);
    sync_->unlock();
}


void Communication::readFromHost()
{
    response_ += socket_->readAll();
    if (response_.contains("\003")) {
        emit sendReaderData(response_);
        emit resume();
        response_.clear();
    }
}
