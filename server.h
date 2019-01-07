#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QVector>
#include "user.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();
    void StartServer();
protected:
    virtual void incomingConnection(qintptr socketDescriptor) override;
private:
   QVector<qintptr> connections;
   QVector<User *> users;
public slots:
   void deleteLater(QString);
   void readyRead(QString);
};

#endif // SERVER_H
