#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextLayout>
#include <QUdpSocket>
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
        //Reading incoming message
        void readPendingDatagrams();

        void on_pushButton_clicked();

        void on_editUser_clicked();

private:
    Ui::MainWindow *ui;

private:
        QUdpSocket *sendS;
        QString nick;
};

#endif // MAINWINDOW_H
