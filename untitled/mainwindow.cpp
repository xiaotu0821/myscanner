#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include<stdio.h>
#include<iostream>
#include<thread>
#include<string>
#include<QString>
#include<string.h>
#include<QLabel>
#include<QTextEdit>
#include<stdlib.h>
#include<QTime>
#include<winsock2.h>
//#pragma comment(lib,"ws2_32.lib")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

class mysocket : public MainWindow
{
public:

    mysocket(int num,int timeout,int port,QString ip):thread_num(num),timeout(timeout),port(port),ip(ip)
    {


    }

    void  run( Ui::MainWindow *ui)
    {

        WORD wVersionRequested;
        WSADATA wsaData;
        int err;
        wVersionRequested = MAKEWORD( 1, 1 );
        err = WSAStartup( wVersionRequested, &wsaData );//初始化
        if(err!=0)
        {
            return ;
        }
        if ( LOBYTE( wsaData.wVersion ) != 1 ||HIBYTE( wsaData.wVersion ) != 1 )
        {
            WSACleanup( );
             return;
        }




          SOCKET cilent=socket(AF_INET,SOCK_STREAM,0);
          SOCKADDR_IN addr;
          addr.sin_family=htons(port);
          addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
          if(::connect(cilent,(SOCKADDR*)&addr,sizeof(SOCKADDR)) < 0)
          {
              QString port_str=QString::number(port,10);
              QString text=ip+"的"+port_str+"不可用";

              ui->textBrowser->setText(text);
          }else
              {
              QString port_str=QString::number(port,10);
              QString text=ip+"的"+port_str+"可用";
             ui->textBrowser->setText(text);
          }






        }





    ~mysocket()
    {



    }


public:

    int  thread_num;
    int  timeout;
    int  port;
    QString ip;


};




void MainWindow::on_pushButton_clicked()
{

    QString port=ui->textEdit_3->toPlainText();
    int    port_num=port.toInt();

    QString thread=ui->textEdit_4->toPlainText();
    int    thread_num=thread.toInt();
    QString timeout=ui->textEdit_5->toPlainText();
    int    timeout_num=timeout.toInt();
    QString ip=ui->textEdit->toPlainText();

    if( ip == ""||port==0 )
    {
        ui->textBrowser->setText("输入 ip 或端口");
        return;
    }else{
        mysocket socket(thread_num,timeout_num,port_num,ip);

        socket.run(ui);
    }



}




void MainWindow::on_pushButton_2_clicked()
{
    QString ipconfig=("ipconfig&pause");

    system(ipconfig.toStdString().c_str());


    ui->textBrowser->setText(ipconfig);
}
