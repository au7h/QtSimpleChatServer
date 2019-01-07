#include "user.h"

User::User(QObject *parent) : QObject(parent)
{

}

void User::setup(qintptr socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    socketDesc = socket->socketDescriptor();
    qDebug() << socketDescriptor;
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void User::write(QString msg)
{
    socket->write(msg.toStdString().c_str());
    socket->flush();
}

void User::readyRead()
{
    QString msg = "<"+QString::number(socket->socketDescriptor())+"> "+socket->readAll();
    emit sendMessage(msg);
}

void User::disconnected()
{
    emit disconnect(QString::number(socketDesc));
}
