#include "filetool.h"
#include <QFile>
#include <QByteArray>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <QDate>
#include <QJsonObject>
#include <QJsonParseError>

FileTool::FileTool(QObject *parent) :
    QObject(parent)
{
}

//检测文件是否有效
bool FileTool::checkFileValid(const QString& file)
{
    QString name = getFileStr(file);
    QFile files(name);
    //判断文件是否存在，或者存在但无内容
    if(!files.exists(name))
    {
        qDebug() <<  (" FileTool.checkFileValid: "+name+" file not exist!") ;
        return false;
    }
    if(!static_cast<bool>(files.size()))
    {
        qDebug() <<  (" FileTool.checkFileValid: "+name+" file is null!") ;
        return false;
    }
    return true;
}

//文件是否存在
bool FileTool::checkExist(QString file)
{
    QString name = getFileStr(file);
    QFile files(name);
    //判断文件是否存在，或者存在但无内容
    if(!files.exists(name))
    {
       files.close();
       return false;
    }
    files.close();
    return true;
}
//判断文件夹是否存在
bool FileTool::checkDirExist(QString file)
{
    QString name = getFileStr(file);
    QDir dir( name );
    if(dir.exists())
    {
       return true;
    }
    return false;
}

//创建全路径
bool FileTool::creatDirAll(QString file)
{
    QString name = getFileStr(file);
    QDir dir;
    return  dir.mkpath( name );
}

//创建子目录
bool FileTool::creatDir(QString file)
{
    QString name = getFileStr(file);
    QDir dir;
    return  dir.mkdir( name );
}

//根据字符串获取目录
QString FileTool::getDir(QString file)
{
    int first = file.lastIndexOf("/");
    return file.left(first);
}

//获取指定文件所有字符内容
QString FileTool::getAllContent(const QString& file)
{
    QString name = getFileStr(file);
    //1:实例化文件类
    QFile files(name);
    //2:打开文件，失败就返回
    if(!files.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug() << ("FileTool.getAllContent : open "+ name +" file error!") ;
        return "";
    }
    //3：实例化字符流类
    QTextStream fs(&files);
    fs.setAutoDetectUnicode(true);
    //4：使用字符流读取文件所有内容
    QString temp = fs.readAll();
    //5: 关闭文件
    files.close();
    //6: 返回内容
    return temp;
}
//获取指定文件所有比特内容
QByteArray FileTool::getAllByte(const QString& file)
{
    QString name = getFileStr(file);
    //1:实例化文件类
    QFile files(name);
    //2:打开文件，失败就返回
    if(!files.open(QIODevice::ReadOnly))
    {
        qDebug() << ("FileTool.getAllByte : open file "+name+" error!") ;
        return "";
    }
    //3：使用字符流读取文件所有内容
    QByteArray byte= files.readAll();
    //4: 关闭文件
    files.close();
    //5: 返回内容
    return byte;
}

//获取过滤注释后的二进制
QByteArray FileTool::getAllJson(const QString& file)
{
    QString name = getFileStr(file);
    //1:实例化文件类
    QFile files(name);
    //2:打开文件，失败就返回
    if(!files.open(QIODevice::ReadOnly))
    {
        qDebug() << ("FileTool::getAllJson : open file "+name+" error!") ;
        return "";
    }
    //3：使用字符流读取文件所有内容
    QByteArray byte;
    while (!files.atEnd())
    {
        QByteArray temp= files.readLine();
        int i=temp.indexOf("//");
        if(i!=-1)
        {
            byte += temp.left(i);
        }
        else byte +=temp;
    }
    //4: 关闭文件
    files.close();
    //5: 返回内容
    return byte;
}

//获取过滤注释后的二进制 qrc地址不需要转换
QByteArray FileTool::getQrcAllJson(const QString& file)
{
    //1:实例化文件类
    QFile files(file);
    //2:打开文件，失败就返回
    if(!files.open(QIODevice::ReadOnly))
    {
        qDebug() << ("FileTool::getQrcAllJson : open file "+file+" error!") ;
        return "";
    }
    //3：使用字符流读取文件所有内容
    QByteArray byte;
    while (!files.atEnd())
    {
        QByteArray temp= files.readLine();
        int i=temp.indexOf("//");
        if(i!=-1)
        {
            byte += temp.left(i);
        }
        else byte +=temp;
    }
    //4: 关闭文件
    files.close();
    //5: 返回内容
    return byte;
}

//获取指定qrc文件所有字符内容
QString FileTool::getQrcAllContent(const QString& file)
{
    //1:实例化文件类
    QFile files(file);
    //2:打开文件，失败就返回
    if(!files.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug() << ("FileTool.getQrcAllContent : open "+ file +" file error!") ;
        return "";
    }
    //3：实例化字符流类
    QTextStream fs(&files);
    fs.setAutoDetectUnicode(true);
    //4：使用字符流读取文件所有内容
    QString temp = fs.readAll();
    //5: 关闭文件
    files.close();
    //6: 返回内容
    return temp;
}

//写二进制数据到文件中
bool FileTool::writeByte(const QString& file,QByteArray& byte)
{
    QString name = getFileStr(file);
    //1:实例化文件类
    QFile files(name);
    if(!files.open(QIODevice::WriteOnly))
    {
        qDebug() <<  ("FileTool.writeByte : open file " + name + " error!") ;
        return false;
    }
    //2:写入数据
    if(files.write(byte) == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}
//写二进制数据到文件中
bool FileTool::writeLog(const QString& file,QByteArray& byte)
{
    QString name = getFileStr(file);
    //1:实例化文件类
    QFile files(name);
    if(!files.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
    {
        qDebug() <<  ("FileTool.writeLog : open file "+name+" error!") ;
        return false;
    }
    //2:写入数据
    if(files.write(byte) == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//重命名文件
bool FileTool::renameFile(const QString& file, QString& newName)
{
    QString name = getFileStr(file);
    //1:实例化文件类
    QFile files(name);
    if(!files.rename(newName)) return false;
    else return true;
}

//删除指定文件
bool FileTool::removeFile(const QString &file)
{
    QString name = getFileStr(file);
    //1:实例化文件类
    return QFile::remove(name);
}
//文件夹获取内部文件路径
QStringList FileTool::getDirFilesAddress(QString dirs)
{
    QStringList list;
    QDir dir(dirs);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList lists = dir.entryInfoList();

    foreach (const QFileInfo &file, lists)
    {
        list << file.absoluteFilePath();
    }
    return list;
}

//复制qrc文件到本地目录
bool FileTool::copyQrcToFile(QString one, QString two)
{
    QString name = getFileStr(two);
    if(!FileTool::checkExist(two))
    {
        //不存在就复制
        if(!QFile::copy(one,name))
        {
            qDebug() << "复制文件 " + one + " 到 " + name + "失败！";
            return false;
        }
        //设置文件权限
        if(!QFile::setPermissions(name,QFileDevice::WriteGroup))
        {
            qDebug() << "设置文件" + name + "权限失败！";
            return false;
        }
    }
    return true;
}

//写log数据
void FileTool::writeLog(QString str)
{
    QString fileName = QDate::currentDate().toString("yyyy-MM-dd");
    QString time     = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    str.prepend(time + "  ");
    QByteArray byt   = str.append("\n").toUtf8();
    FileTool::writeLog(fileName,byt);
}

//处理不同系统文件路径问题
QString FileTool::getFileStr(QString file)
{
    QString name = "";
    #ifdef Q_OS_IOS
       name = QDir::homePath() + "/Documents/";
    #endif
    name = name + file;
    return name;
}

//转换byte 为 json
QJsonObject FileTool::byteToJson(const QByteArray &byte)
{
    QJsonParseError error;
    QJsonDocument doc  = QJsonDocument::fromJson(byte,&error);
    if(error.error != QJsonParseError::NoError)
    {
        //抛出异常
        QT_THROW(error.errorString());
    }
    QJsonObject json = doc.object();
    return json;
}
