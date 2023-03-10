#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void startThread();

private:
    Ui::MainWindow *ui;
    QVector<QString> data_{};

signals:
    void finished();
    void sendSequence(QByteArray);
};
#endif // MAINWINDOW_H
