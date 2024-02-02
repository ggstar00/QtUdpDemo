#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbtn_connect_clicked();

    void on_pbtn_disconnect_clicked();

    void on_pbtn_clear_clicked();

    void on_pbtn_exit_clicked();

    void on_pbtn_findip_clicked();

    QString getlocalip();

    void readPendingDatagrams();


    void on_pbtn_send_clicked();

    void on_pbtn_broadcast_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *udpsocket;

signals:
    void readyRead();
};
#endif // MAINWINDOW_H
