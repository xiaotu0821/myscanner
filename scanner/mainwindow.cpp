#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include<stdio.h>
#include<iostream>
#include<thread>
#include<QString>
#include<string.h>
#include<QByteArray>
#include<QLabel>
#include<QTextEdit>
#include<stdlib.h>
#include<error.h>
#include<winsock2.h>
#include<thread>
#pragma comment(lib,"Ws2_32")


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
          addr.sin_family=AF_INET;
           addr.sin_port=htons(port);
          QByteArray tmp = ip.toLatin1();
          char*ip1=tmp.data();
          addr.sin_addr.S_un.S_addr = inet_addr(ip1);
          int len =1;
          int error=-1;
          getsockopt(cilent, SOL_SOCKET, SO_ERROR, (char*)&error, &len);
             ui->textBrowser->clear();
          while(port>0)
          {
             addr.sin_port=htons(port);
             int ret=::connect(cilent,(SOCKADDR*)&addr,sizeof(SOCKADDR_IN));
          if(0==ret)
          {   port--;
              QString port_str=QString::number(port,10);
              QString text=ip+"的"+port_str+"可用";

              ui->textBrowser->append(text);
              closesocket(cilent);

          }else
              {

              QString port_str=QString::number(port,10);
              QString text=ip+"的"+port_str+"不可用";

              ui->textBrowser->append(text);
              port--;
          }

        }
        WSACleanup();
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

void MainWindow::on_pushButton_3_clicked()
{
    exit(0);
}
