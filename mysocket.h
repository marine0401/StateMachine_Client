#ifndef MYSOCKET_H
#define MYSOCKET_H
#include<QObject>
#include<QTcpSocket>
#include<QTcpServer>
#include<QDebug>
class MySocket : public QObject
{
    Q_OBJECT
public:
    MySocket();
    ~MySocket();

public slots:
    void init(QString ip,quint16 port);
    void read();
    void on_to_get_message();
    void on_to_disconnect();
signals:
    void get_message(QByteArray macAddress);
private:
    QTcpSocket *m_socket;
    QByteArray receive_buffer;
    QByteArray send_buffer;

};

#endif // MYSOCKET_H
