#ifndef POSNETTEST_H
#define POSNETTEST_H

#include <QByteArray>
#include <QMutex>
#include <QObject>
#include <QString>
#include <QVector>
#include <QWaitCondition>

class PosnetTest : public QObject
{
    Q_OBJECT
public:
    explicit PosnetTest(const QVector<QString>& sequneces);
    ~PosnetTest();

public slots:
    void startTask();
    void pauseTask();
    void resumeTask();

private:
    QVector<QString> sequences_{};
    QWaitCondition pauseCond_;
    bool pause_{false};
    QMutex sync_;

signals:
    void sendSequence(QByteArray);
    void finished();
};

#endif // POSNETTEST_H
