#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QUdpSocket;
class QFile;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QUdpSocket* _udp_socket = nullptr;
    quint16 _port = 2121;
    QFile* file = nullptr;
    Ui::MainWindow *ui;
    quint64 _len = 256;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void sendMessage();
private slots:
   void ReadyRead();
   void on_UDPWrite_clicked();
};
#endif // MAINWINDOW_H
