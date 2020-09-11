#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QUdpSocket>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit,SIGNAL(returnPressed()),SLOT(sendMessage()));
    _udp_socket = new QUdpSocket(this);
    //ready for listen
    _udp_socket->bind(_port);
    connect(_udp_socket,SIGNAL(readyRead()),SLOT(ReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMessage()
{
    if (!_udp_socket) return;
    QByteArray ba = ui->lineEdit->text().toLocal8Bit();
    _udp_socket->writeDatagram(ba,QHostAddress::Broadcast,_port);
}

void MainWindow::on_UDPWrite_clicked()
{
    sendMessage();
}

void MainWindow::ReadyRead()
{
    if (!_udp_socket) return;
    while (_udp_socket->hasPendingDatagrams())
    {
       char buffer[_len-1];
       QHostAddress address(ui->lineEdit->text());
       _udp_socket->readDatagram(buffer,_len,&address,&_port);
       ui->textEdit->append(buffer);
    }
}
