#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QMutex>
#include <QAbstractSocket>

class Communication : public QObject
{
    Q_OBJECT

public:
    Communication(const QString &hostName = QString(), quint16 port = 0);
    ~Communication();

    void connectToHost(const QString &hostName, quint16 port);
    void disconnectFromHost();

    void writeToHost(const QByteArray &data);
    void readFromHost();

private:
    QTcpSocket* socket_;
    QByteArray response_;
    QMutex* sync_;

signals:
    void sendWritedData(QByteArray);
    void sendReaderData(QByteArray);
    void resume();
    void pause();
};

#endif // COMMUNICATION_H
