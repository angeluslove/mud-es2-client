#include "color.h"
#include <QDebug>

color::color(QObject *parent) :
    QObject(parent)
{
    esc.append(char(27));

    m_color.insert(esc+"[1m","<font style=\"font-weight:bold\">"); //加粗
    m_color.insert(esc+"[30m", "<font style=\"color:#000000\">" ); //黑色

    //前景色
    m_color.insert(esc+"[1;30m","<font style=\"color:#808080\">"); //灰色
    m_color.insert(esc+"[31m","<font style=\"color:#800000\">");   //暗红
    m_color.insert(esc+"[1;31m","<font style=\"color:#ff0000\">"); //亮红
    m_color.insert(esc+"[32m","<font style=\"color:#008000\">");   //暗绿
    m_color.insert(esc+"[1;32m","<font style=\"color:#00ff00\">"); //亮绿
    m_color.insert(esc+"[33m","<font style=\"color:#808000\">");   //暗黄
    m_color.insert(esc+"[1;33m","<font style=\"color:#ffff00\">"); //亮黄
    m_color.insert(esc+"[34m","<font style=\"color:#000080\">");   //暗蓝
    m_color.insert(esc+"[1;34m","<font style=\"color:#0000ff\">"); //亮蓝
    m_color.insert(esc+"[35m","<font style=\"color:#800080\">");   //暗紫
    m_color.insert(esc+"[1;35m","<font style=\"color:#ff00ff\">"); //亮紫
    m_color.insert(esc+"[36m","<font style=\"color:#008080\">");   //暗靛
    m_color.insert(esc+"[1;36m","<font style=\"color:#00ffff\">"); //亮靛
    m_color.insert(esc+"[37m","<font style=\"color:#c0c0c0\">");   //暗白
    m_color.insert(esc+"[1;37m","<font style=\"color:#ffffff\">"); //亮白
    m_color.insert(esc+"[37;1m","<font style=\"color:#ffffff\">"); //亮白

    //背景色
    m_color.insert(esc+"[40m","<font style=\"background-color:#000000\">"); //黑色
    m_color.insert(esc+"[41m","<font style=\"background-color:#ff0000\">"); //红色
    m_color.insert(esc+"[42m","<font style=\"background-color:#00ff00\">"); //绿色
    m_color.insert(esc+"[43m","<font style=\"background-color:#ffff00\">"); //黄色
    m_color.insert(esc+"[44m","<font style=\"background-color:#0000ff\">"); //蓝色
    m_color.insert(esc+"[45m","<font style=\"background-color:#ff00ff\">"); //紫色
    m_color.insert(esc+"[46m","<font style=\"background-color:#00ffff\">"); //亮靛
    m_color.insert(esc+"[47m","<font style=\"background-color:#ffffff\">"); //亮白

    m_color.insert(esc+"[2;37;0m","</font>"); //结束符
}

QString color::cheackColor(QByteArray data)
{
    //处理制表符
    data.replace("\r\n","<br>");   //换行字符
    data.replace("\n"  ,"<br>");   //换行字符
    data.replace(" ","&nbsp;");    //空格字符
    data.replace("\t","&nbsp;&nbsp;&nbsp;&nbsp;");  //制表符TAB

    QByteArray b;
    QByteArray nor(esc+"[2;37;0m");
    int  x = 0;
    bool s = false;
    while(true)
    {
        int i = data.indexOf(char(27),x);
        if(i == -1) break;
        else
        {
            int e = data.indexOf(char(109),i);
            if(e == -1)
            {
                x = i + 1;
            }
            else
            {
                e = e - i + 1;
                b = data.mid(i,e);
                //是否需要添加结束符
                if(b != nor)
                {
                    //再遇到颜色就自动结束前一个颜色
                    if(s)
                    {
                        data.insert(i,m_color.value(nor));
                        s = false;
                        continue;
                    }
                    s = true;
                }

                //查找符合条件的替换掉
                data.replace(i,e,m_color.value(b));
            }
        }
    }

    QString m = data;
    return data;
}
