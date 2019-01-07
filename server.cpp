#include "server.h"
#include "user.h"

Server::Server(QObject *parent) : QTcpServer (parent)
{
}

Server::~Server()
{
}

void Server::StartServer()
{
    if(!this->listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Could not start server";
        qDebug() << "Details: " << this->errorString();
    }
    else {
        qDebug() << "Listening on localhost port 1234";
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    User *user= new User(this);
    user->setup(socketDescriptor);

    connect(user, SIGNAL(disconnect(QString)), user, SLOT(deleteLater()), Qt::QueuedConnection);
    connect(user, SIGNAL(disconnect(QString)), this, SLOT(deleteLater(QString)), Qt::QueuedConnection);
    connect(user, SIGNAL(sendMessage(QString)), this, SLOT(readyRead(QString)), Qt::QueuedConnection);

    users.append(user);
    QVectorIterator<User *> usersIterator(users);
    while(usersIterator.hasNext())
    {
        QString welcomeMsg = "Użytkownik " + QString::number(socketDescriptor) +" dołączył do czatu\n";
        usersIterator.next()->write(welcomeMsg.toStdString().c_str());
    }
    qDebug() << "Users online: " << users.size();

}

void Server::deleteLater(QString socketDescriptor)
{
    QVectorIterator<User *> usersIterator(users);
    while(usersIterator.hasNext())
    {
        usersIterator.next()->write("Uzytkownik "+socketDescriptor+" opuścił pokój\n");
    }

    users.removeLast();

}

void Server::readyRead(QString msg)
{
    QVectorIterator<User *> usersIterator(users);
    while(usersIterator.hasNext())
    {
        usersIterator.next()->write(msg);
    }
}
