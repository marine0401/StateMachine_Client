#ifndef MAINWINDOW_H
#define MAINWINDOW_H
extern "C"{
    #include"qrencode-4.1.0/qrencode.h"
}
#include<QPainter>
#include <QMainWindow>
#include"mysocket.h"
#include<QThread>
#include<QTcpSocket>
#include<QString>
#include<QList>
#include<QJsonArray>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void get_ip_port(QString ip,quint16 port);
    void to_get_message();
    void to_disconnect();
private slots:
    void on_getMessage_clicked();

    void on_connect_clicked();

    void on_disconnect_clicked();

public slots:
    void on_get_message(QByteArray macAddress);




private:
    Ui::MainWindow *ui;
    QThread *m_socket_Thread;
    MySocket *m_socket;
    void GenerateQRcode(QString tempstr);

    QString addColon(const QString &str1, const QString &str2);

};
#endif // MAINWINDOW_H
