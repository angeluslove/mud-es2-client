#include "mytcpsocket.h"
#include <QDebug>
#include <QDataStream>
#include <QByteArray>
#include <QAbstractSocket>

#include "filetool.h"


myTcpSocket::myTcpSocket(QObject *parent) :  QObject(parent)
{
    this->init();
    //初始化指针
    this->socket= new QTcpSocket();
    //设定加密连接参数
    //连接套接字信号
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(socket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(connectState(QAbstractSocket::SocketState)));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(error(QAbstractSocket::SocketError)));
}
myTcpSocket::~myTcpSocket()
{
    qDebug() << "myTcpSocket is delete";
    delete socket;
}

//连接状态改变
void myTcpSocket::connectState(QAbstractSocket::SocketState socketState)
{
    QString temp = "";
    switch(socketState)
    {
        case QAbstractSocket::UnconnectedState:
        case QAbstractSocket::ClosingState:     temp = QStringLiteral("正在断开中...");  break;
        case QAbstractSocket::HostLookupState:  temp = QStringLiteral("握手中...");  break;
        case QAbstractSocket::ConnectingState:  temp = QStringLiteral("正在连接中..."); break;
        default: return;
    }
    emit this->upQmlMessage(temp );
}
//连接错误信息
void myTcpSocket::error(QAbstractSocket::SocketError socketError)
{
    QString temp="";
    switch (socketError)
    {
        case QAbstractSocket::ConnectionRefusedError:
             temp = QStringLiteral("连接被服务器拒绝！"); break;
        case QAbstractSocket::RemoteHostClosedError:
             temp = QStringLiteral("远程服务器已关闭！"); break;
        case QAbstractSocket::HostNotFoundError:
             temp = QStringLiteral("无法找到远程服务器！"); break;
        case QAbstractSocket::SocketTimeoutError:
             temp = QStringLiteral("连接超时！"); break;
        case QAbstractSocket::NetworkError:
             temp = QStringLiteral("网络错误！"); break;
        case QAbstractSocket::SslHandshakeFailedError:
             temp = QStringLiteral("加密连接握手错误！"); break;
        default:
             temp = QStringLiteral("其他错误,请联系管理人员 ！"); break;
    }
    emit this->upQmlMessage("error: "+temp);
}

//初始化变量
void myTcpSocket::init()
{
    m_ip   = "127.0.0.1";
    m_port = 9999;
    //获取配置文件
    QString config = FileTool::getAllContent("config.ini");
    if(!config.isEmpty())
    {
        QStringList con = config.split(":");
        m_ip   = con.first();
        m_port = con.last().toInt();
    }
}

//开始连接服务器
void myTcpSocket::startConnectServer()
{
    quint16 ports = static_cast<quint16>(m_port);
    this->socket->connectToHost(m_ip,ports);
}
//主动断开服务器连接
void myTcpSocket::abortServer()
{
    this->socket->abort();
}
//发送命令
void myTcpSocket::sendServerData(QString cmd)
{
    QByteArray byte;
    byte.append( cmd.toUtf8() );
    byte.append(QChar(10));
    this->sendData(byte);
}

//连接服务器
void myTcpSocket::connected()
{
    QString msg= QStringLiteral("连接成功！");
    emit this->upQmlMessage(msg);
}
//服务器断开后执行函数
void myTcpSocket::disconnected()
{
    emit this->upClose();
}


//接收服务端数据函数
void myTcpSocket::readData()
{
    QByteArray byte;
    //接收
    if(this->socket->bytesAvailable())
    {
        //读取所有数据
        byte = this->socket->readAll();
        qDebug() << QString(byte);
    }
    QString msg = handleColor(byte);
    emit this->upQmlMessage(msg);
}

//私有的，发送数据
void myTcpSocket::sendData(QByteArray &data)
{
    //写入到套接字中发送
    this->socket->write(data);
    this->socket->waitForBytesWritten();
    this->socket->flush();
}

//处理颜色
QString myTcpSocket::handleColor(QByteArray data)
{
    return m_color.cheackColor(data);
}


