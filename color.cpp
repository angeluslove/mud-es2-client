#include "color.h"
#include <QDebug>

color::color(QObject *parent) :
    QObject(parent)
{
    esc.append(char(27));

    m_color.insert(esc+"[1m","<font style=\"font-weight:bold\">"); //�Ӵ�
    m_color.insert(esc+"[30m", "<font style=\"color:#000000\">" ); //��ɫ

    //ǰ��ɫ
    m_color.insert(esc+"[1;30m","<font style=\"color:#808080\">"); //��ɫ
    m_color.insert(esc+"[31m","<font style=\"color:#800000\">");   //����
    m_color.insert(esc+"[1;31m","<font style=\"color:#ff0000\">"); //����
    m_color.insert(esc+"[32m","<font style=\"color:#008000\">");   //����
    m_color.insert(esc+"[1;32m","<font style=\"color:#00ff00\">"); //����
    m_color.insert(esc+"[33m","<font style=\"color:#808000\">");   //����
    m_color.insert(esc+"[1;33m","<font style=\"color:#ffff00\">"); //����
    m_color.insert(esc+"[34m","<font style=\"color:#000080\">");   //����
    m_color.insert(esc+"[1;34m","<font style=\"color:#0000ff\">"); //����
    m_color.insert(esc+"[35m","<font style=\"color:#800080\">");   //����
    m_color.insert(esc+"[1;35m","<font style=\"color:#ff00ff\">"); //����
    m_color.insert(esc+"[36m","<font style=\"color:#008080\">");   //����
    m_color.insert(esc+"[1;36m","<font style=\"color:#00ffff\">"); //����
    m_color.insert(esc+"[37m","<font style=\"color:#c0c0c0\">");   //����
    m_color.insert(esc+"[1;37m","<font style=\"color:#ffffff\">"); //����
    m_color.insert(esc+"[37;1m","<font style=\"color:#ffffff\">"); //����

    //����ɫ
    m_color.insert(esc+"[40m","<font style=\"background-color:#000000\">"); //��ɫ
    m_color.insert(esc+"[41m","<font style=\"background-color:#ff0000\">"); //��ɫ
    m_color.insert(esc+"[42m","<font style=\"background-color:#00ff00\">"); //��ɫ
    m_color.insert(esc+"[43m","<font style=\"background-color:#ffff00\">"); //��ɫ
    m_color.insert(esc+"[44m","<font style=\"background-color:#0000ff\">"); //��ɫ
    m_color.insert(esc+"[45m","<font style=\"background-color:#ff00ff\">"); //��ɫ
    m_color.insert(esc+"[46m","<font style=\"background-color:#00ffff\">"); //����
    m_color.insert(esc+"[47m","<font style=\"background-color:#ffffff\">"); //����

    m_color.insert(esc+"[2;37;0m","</font>"); //������
}

QString color::cheackColor(QByteArray data)
{
    //�����Ʊ��
    data.replace("\r\n","<br>");   //�����ַ�
    data.replace("\n"  ,"<br>");   //�����ַ�
    data.replace(" ","&nbsp;");    //�ո��ַ�
    data.replace("\t","&nbsp;&nbsp;&nbsp;&nbsp;");  //�Ʊ��TAB

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
                //�Ƿ���Ҫ��ӽ�����
                if(b != nor)
                {
                    //��������ɫ���Զ�����ǰһ����ɫ
                    if(s)
                    {
                        data.insert(i,m_color.value(nor));
                        s = false;
                        continue;
                    }
                    s = true;
                }

                //���ҷ����������滻��
                data.replace(i,e,m_color.value(b));
            }
        }
    }

    QString m = data;
    return data;
}
