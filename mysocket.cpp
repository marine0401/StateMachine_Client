#include "mysocket.h"
#include "protocol.h"
MySocket::MySocket() :QObject()
{
//    send_buffer.reserve(3);
//    send_buffer.append(0x57);
//    send_buffer.append(0x01);
//    send_buffer.append(0x01);
}

MySocket::~MySocket()
{

}

void MySocket::init(QString ip,quint16 port)
{
    m_socket = new QTcpSocket();
    m_socket->connectToHost(ip,port);

//    connect(m_socket,&QTcpSocket::disconnected,[=](){
//        delete m_socket;
//        m_socket = nullptr;
//    });

    connect(m_socket,&QTcpSocket::readyRead,this,&MySocket::read);



}
void MySocket::read()
{
    receive_buffer.append(m_socket->readAll());
    char *dataPtr = receive_buffer.data();

    Packet* packetPtr = (Packet *)dataPtr;
    qDebug() << "packet sync" << packetPtr->sync<<endl;
    qDebug() << "packet length" << packetPtr->length<<endl;



    char *dat = receive_buffer.data();
    int j =0;

     while (j < packetPtr->length) {
         qDebug() << " [" << QByteArray(1,*dat).toHex() << "] " ;
         ++dat;
         ++j;
     }



    QByteArray temp;
    if(receive_buffer.size() > 3)
    {
        if(packetPtr->sync ==SYNC)
        {
            if(receive_buffer.size() >= packetPtr->length)
            {
                if(packetPtr->cmdID == 0x01)
                {
                    qint64 dataLen = packetPtr->length - 4; //数据长度
                    char * data = (char *)malloc(dataLen);
                    memcpy(data,dataPtr+4,dataLen);

                    temp.append(data);
                    temp.remove(0,1);
                    if(data[0] & 0x01)
                    {

                         emit get_message(temp.left(17));
                        temp.remove(0,17);
                    }
                    delete data;
                    receive_buffer.remove(0,packetPtr->length);
                }
            }
        }
    }
}

void MySocket::on_to_get_message()
{
//    send_buffer.append(0x01);
//    send_buffer.append(0x01);
//    send_buffer[2] = ((unsigned short)send_buffer.size() >> 8) & 0xff;
//    send_buffer[1] = (unsigned short)(send_buffer.size()) & 0xff;

    m_socket->write(getMacAddress());
    m_socket->waitForBytesWritten();
//    send_buffer.remove(3,3);
}


void MySocket::on_to_disconnect()
{
    m_socket->disconnectFromHost();
}
