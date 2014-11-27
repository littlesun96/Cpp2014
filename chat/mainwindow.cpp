#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    this->Login->setText("Your nickname");

    this->sendS = new QUdpSocket(this);
    this->sendS->bind(QHostAddress::Any, 3333, QUdpSocket::ReuseAddressHint);
    connect(this->sendS, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readPendingDatagrams()
{
    while (this->sendS->hasPendingDatagrams())
    {
        QByteArray datas;
        datas.resize(this->sendS->pendingDatagramSize());
        this->sendS->readDatagram(datas.data(), datas.size());
        QString string = QString::fromUtf8(datas).trimmed();
        QString nickName = "";
        for(int i = 1; i < string.size(); i++)
        {
            if(string[i] == '>') break;
            nickName+=string[i];
        }
        bool toShow = true;
        for(int i = 0 ; i < this->Logins->count();i++)
        {
            if(this->Logins->item((i))->text() == nickName)
                toShow = false;
        }
        if(toShow) new QListWidgetItem(nickName, this->Logins);
        new QListWidgetItem(string, this->Messages);


    }
}

void MainWindow::on_pushButton_clicked()
{
    if(this->nick == "")
        {
            this->writeMessage->setText("Set nickname first!");
            return;
        }
    if(this->writeMessage->toPlainText() == "")
    {
        return;
    }
    QString toSend = "<" + this->nick + ">: "+ this->writeMessage->toPlainText();
    QByteArray message;
    message.append(toSend);
    this->sendS->writeDatagram(message.data(), message.size(), QHostAddress::Broadcast, 3333);
    this->writeMessage->setText("");
}

void MainWindow::on_editUser_clicked()
{
    if (this->nick != "") {
        return;
    }
    if (this->Login->text() == "")
        {
            this->Login->setText("Insert your nickname");
        }
    this->nick = this->Login->text();
    this->Login->setReadOnly(true);
    this->writeMessage->setText("");
    QString sendData = "<" + this->nick + ">: My first message";
    QByteArray message;
    message.append(sendData);
    this->sendS->writeDatagram(message.data(), message.size(), QHostAddress::Broadcast, 3333);
}
