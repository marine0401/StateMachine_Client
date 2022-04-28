#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "1" <<endl;
    m_socket = new MySocket();
    m_socket_Thread = new QThread();
    m_socket->moveToThread(m_socket_Thread);
    connect(m_socket_Thread,&QThread::finished,m_socket,&MySocket::deleteLater);
    connect(this,&MainWindow::get_ip_port,m_socket,&MySocket::init);
    connect(this,&MainWindow::to_get_message,m_socket,&MySocket::on_to_get_message);
    connect(this,&MainWindow::to_disconnect,m_socket,&MySocket::on_to_disconnect);
    connect(m_socket,&MySocket::get_message,this,&MainWindow::on_get_message);
    m_socket_Thread->start();





}

MainWindow::~MainWindow()
{
    m_socket_Thread->quit();
    m_socket_Thread->wait();
    delete ui;

}


void MainWindow::on_getMessage_clicked()
{
    emit to_get_message();
}

void MainWindow::on_connect_clicked()
{
    emit get_ip_port(ui->ip->text(),ui->port->text().toInt());
}

void MainWindow::on_disconnect_clicked()
{
    emit to_disconnect();
}

void MainWindow::on_get_message(QByteArray macAddress)
{
    QList<QString> l;
    l.append(QString(macAddress));
    qDebug() << l.at(0) <<endl;
    QJsonArray jl;
    jl = QJsonArray::fromStringList(l);
    qDebug() << jl.at(0) <<endl;
    QString temp = "{" + addColon("deviceName","rk3568") +","
            +addColon("deviceID",QString(macAddress)) +"," + addColon("deviceType","Cortex-A55")  +  "}";
    GenerateQRcode(temp);
    ui->display->setText(QString(macAddress));
}
QString MainWindow::addColon(const QString &str1, const QString &str2)
{
    return QString("\""+str1+"\" : \" "  + str2 + "\"");
}
void MainWindow::GenerateQRcode(QString tempstr)
{
    QRcode *qrcode; //二维码数据
    //QR_ECLEVEL_Q 容错等级
    qrcode = QRcode_encodeString(tempstr.toStdString().c_str(), 2, QR_ECLEVEL_Q, QR_MODE_8, 1);
    qint32 temp_width=ui->renCode->width(); //二维码图片的大小
    qint32 temp_height=ui->renCode->height();
    qint32 qrcode_width = qrcode->width > 0 ? qrcode->width : 1;
    double scale_x = (double)temp_width / (double)qrcode_width; //二维码图片的缩放比例
    double scale_y =(double) temp_height /(double) qrcode_width;
    QImage mainimg=QImage(temp_width,temp_height,QImage::Format_ARGB32);
    QPainter painter(&mainimg);
    QColor background(Qt::white);
    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, temp_width, temp_height);
    QColor foreground(Qt::black);
    painter.setBrush(foreground);
    for( qint32 y = 0; y < qrcode_width; y ++)
    {
        for(qint32 x = 0; x < qrcode_width; x++)
        {
            unsigned char b = qrcode->data[y * qrcode_width + x];
            if(b & 0x01)
            {
                QRectF r(x * scale_x, y * scale_y, scale_x, scale_y);
                painter.drawRects(&r, 1);
            }
        }
    }
    QPixmap mainmap=QPixmap::fromImage(mainimg);
    ui->renCode->setPixmap(mainmap);
    ui->renCode->setVisible(true);
}

