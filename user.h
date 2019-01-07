#ifndef USER_H
#define USER_H

#include <QObject>
#include <QTcpSocket>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    void setup(qintptr socketDescriptor);
    void write(QString msg);

signals:
    void sendMessage(QString);
    void disconnect(QString);

public slots:
    void readyRead();
    void disconnected();

public:
    QTcpSocket *socket;
    qintptr socketDesc;
};

#endif // USER_H
