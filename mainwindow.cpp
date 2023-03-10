#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include "posnettest.h"
#include "communication.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::startThread);

    data_.push_back("\02servicerep\t#6227\03");
    data_.push_back("\02rtcget\t#7D61\03");
    data_.push_back("\02trinit\t#911D\03");
    data_.push_back("\02trline\tnaTowar A\tvt0\tpr9999999\t#712E\03");
    data_.push_back("\02trend\tto9999999\t#CC47\03");
    data_.push_back("\02rtcget\t#7D61\03");
    data_.push_back("\02dailyrep\tda2023-03-09,17:58\t#0AE8\03");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startThread()
{
    QThread* commThread = new QThread;
    Communication* socket = new Communication("192.168.0.102", 6666);
    PosnetTest* posnet = new PosnetTest(data_);
    socket->moveToThread(commThread);
    posnet->moveToThread(commThread);

    connect(commThread, &QThread::started, posnet, &PosnetTest::startTask);
    connect(posnet, &PosnetTest::sendSequence, socket, &Communication::writeToHost, Qt::DirectConnection);
    connect(socket, &Communication::pause, posnet, &PosnetTest::pauseTask, Qt::DirectConnection);
    connect(socket, &Communication::resume, posnet, &PosnetTest::resumeTask, Qt::DirectConnection);
    connect(socket, &Communication::sendWritedData, ui->textBrowserIn, &QTextBrowser::append, Qt::DirectConnection);
    connect(socket, &Communication::sendReaderData, ui->textBrowserOut, &QTextBrowser::append, Qt::DirectConnection);
    connect(posnet, &PosnetTest::finished, commThread, &QThread::quit);
    connect(posnet, &PosnetTest::finished, socket, &Communication::deleteLater);
    connect(posnet, &PosnetTest::finished, posnet, &PosnetTest::deleteLater);
    connect(commThread, &QThread::finished, commThread, &QThread::deleteLater);

    commThread->start();
}
