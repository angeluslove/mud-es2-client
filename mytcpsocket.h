#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QSslSocket>
#include <QFile>
#include "color.h"

class myTcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit myTcpSocket(QObject *parent = nullptr);
    ~myTcpSocket();



signals:
    void upQmlMessage(QString msg);                    //发送到前台文本信息
    void upClose();                                    //连接断开

public slots:
    void startConnectServer();                                      //连接服务器
    void abortServer();                                             //主动断开服务器连接
    void sendServerData(QString cmd);                               //发送命令
    //------------------------------------------------------------------

private slots:

    void readData();                                                //读取服务器端数据
    void disconnected();                                            //连接断开
    void connected();                                               //加密连接完成
    void connectState(QAbstractSocket::SocketState socketState);    //连接状态
    void error(QAbstractSocket::SocketError socketError);           //错误处理

private:
    QTcpSocket*  socket;                                              //客户端socket
    QString      m_ip;                                                //ip
    int          m_port;                                              //port
    color        m_color;                                             //color类

    const     qint64 m_size0  = static_cast<qint64>(0);               //转换0大小
    const     qint64 m_size64 = static_cast<qint64>(sizeof(qint64));  //转换类型大小

    //----------------------------------------------------------------私有成员函数
    void init();
    void sendData(QByteArray  &data);              //发送数据到服务端
    QString handleColor(QByteArray data);          //处理颜色
};

#endif // MYTCPSOCKET_H
