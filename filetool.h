#ifndef SHARE_H
#define SHARE_H

#include <QObject>
//-----------------------
//文件工具类,
//主要是放置一些操作文件静态函数
//-----------------------

class FileTool : public QObject
{
    Q_OBJECT
public:
    explicit FileTool(QObject *parent = nullptr);

    static bool checkFileValid(const QString& file);                                 //查看给定文件是否有效
    static bool checkExist(QString file);                                            //文件是否存在
    static bool checkDirExist(QString file);                                         //判断文件夹是否存在
    static bool creatDir(QString file);                                              //创建子目录
    static bool creatDirAll(QString file);                                           //创建全路径
    static QString getDir(QString file);                                             //根据字符串获取目录
    static bool removeFile(const QString& file);                                     //删除指定文件
    static QStringList getDirFilesAddress(QString dirs);                             //根据文件夹获取内部文件路径
    static bool renameFile(const QString& file,QString& newName);                    //重新命名文件
    
    static QString getAllContent(const QString& file);                               //获取文件内的内容
    static QByteArray getAllByte(const QString& file);                               //获取文件二进制内容
    static QByteArray getAllJson(const QString& file);                               //获取过滤注释后json文件
    
    static bool writeByte(const QString& file,QByteArray& byte);                     //写二进制数据到文件中
    static bool writeLog(const QString& file,QByteArray& byte);                      //写二进制数据到文件中
    
    static QString getQrcAllContent(const QString& file);                            //获取qrc文件内的内容
    static QByteArray getQrcAllJson(const QString& file);                            //获取qrcjson文件

    static bool copyQrcToFile(QString one,QString two);                              //复制qrc文件到本地目录

    //写log数据
    static void writeLog(QString str);

    //处理不同系统文件路径问题
    static QString getFileStr(QString file);

    //转换byte 为 json
    static QJsonObject byteToJson(const QByteArray &byte);
};

#endif // SHARE_H
