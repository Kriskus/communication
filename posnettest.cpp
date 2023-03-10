#include "posnettest.h"
#include <QThread>

#include <QApplication>

#include <QDebug>

PosnetTest::PosnetTest(const QVector<QString> &sequneces)
    : sequences_(sequneces)
{}

PosnetTest::~PosnetTest()
{}

void PosnetTest::startTask()
{
    for(QString& sequence: sequences_) {
        emit sendSequence(sequence.toLatin1());

        sync_.lock();
        if(pause_)
            pauseCond_.wait(&sync_);
        sync_.unlock();
    }
    emit finished();
}

void PosnetTest::pauseTask() {
    sync_.lock();
    pause_ = true;
    sync_.unlock();
}

void PosnetTest::resumeTask() {
    sync_.lock();
    pause_ = false;
    sync_.unlock();
    pauseCond_.wakeAll();
}
