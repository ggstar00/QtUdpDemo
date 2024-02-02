#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    udpsocket = new QUdpSocket(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    udpsocket->abort();
    delete udpsocket;
}

void MainWindow::on_pbtn_connect_clicked()
{
    QString ip = ui->lineEdit_ip->text();
    quint16 port = ui->bind_port->text().toUShort();
    udpsocket->bind(port);//绑定IP地址和端口号
    connect(udpsocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));//接收数据
    ui->textEdit_display->append("连接成功");
}


void MainWindow::on_pbtn_disconnect_clicked()
{
    udpsocket->abort();//断开连接
    ui->textEdit_display->append("断开连接");
}


void MainWindow::on_pbtn_clear_clicked()
{
    ui->textEdit_display->clear();//清空显示区域
}


void MainWindow::on_pbtn_exit_clicked()
{
    exit(0);//退出程序
}


void MainWindow::on_pbtn_findip_clicked()
{
    ui->textEdit_display->append(getlocalip());//显示本机IP地址
    ui->lineEdit_ip->setText(getlocalip());
}

QString MainWindow::getlocalip()
{
    QString localip;
    //获取本机IPv4地址
    QString localHostName = QHostInfo::localHostName();//本地主机名
    QHostInfo info = QHostInfo::fromName(localHostName);//主机信息
    QList<QHostAddress> list = info.addresses();//地址列表
    foreach(QHostAddress address, list){
        if(address.protocol() == QAbstractSocket::IPv4Protocol){
            localip = address.toString();
        }
    }
    return localip;
}

void MainWindow::readPendingDatagrams()
{
    while(udpsocket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(udpsocket->pendingDatagramSize());
        QHostAddress peerAddr;
        quint16 peerPort;
        udpsocket->readDatagram(datagram.data(),datagram.size(),&peerAddr,&peerPort);
        QString str = datagram.data();
        
        QString peer = "[From " + peerAddr.toString() + ":" + QString::number(peerPort) + "]";

        ui->textEdit_display->append(peer + str);
                
    }
}





void MainWindow::on_pbtn_send_clicked()
{
    QString message = ui->lineEdit_message->text();
    QString ip = ui->lineEdit_ip->text();
    quint16 port = ui->global_port->text().toUShort();
    QByteArray datagram = message.toUtf8();
    udpsocket->writeDatagram(datagram,QHostAddress(ip),port);
    ui->textEdit_display->append("发送成功");
}


void MainWindow::on_pbtn_broadcast_clicked()
{
    QString message = ui->lineEdit_message->text();
    quint16 port = ui->global_port->text().toUShort();
    QByteArray datagram = message.toUtf8();
    udpsocket->writeDatagram(datagram,QHostAddress::Broadcast,port);
    ui->textEdit_display->append("广播成功");
}

