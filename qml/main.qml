import QtQuick 2.12
import QtQuick.Controls 2.12
/*
*  主要界面非常的简单,主要是为了显示,以后可能为了扩展会增加qml文件,但现在足够了！
*  按钮可以单独写个按钮控件,这里为了简单就直接写了.
*/
ApplicationWindow
{
    id      : root
    visible : true
    width   : 600
    height  : 500
    color   : "black"
    //---------------------------------------------------------
    property bool   isCon    : false          //是否连接状态

    //初始化
    function init()
    {

    }
    //接收信号
    Connections
    {
        target: cli          //信号发送者
        onUpQmlMessage:      //接收文本信息(参数为 QString msg)
        {
            addMsg(msg);
        }
        onUpClose:
        {
            isCon = false;
        }
    }

    function addMsg(msg)
    {
        message.text += "<br>" + msg;
        view.contentY = view.contentHeight - view.height + message.lineHeight;
    }

    //-----------------------------------------------

    //-----------------------------------------------竖排列
    Column
    {
        anchors.fill: parent

        Flickable
        {
            id: view
            width  : parent.width
            height : parent.height * 0.83
            contentWidth : width
            contentHeight: message.paintedHeight
            clip: true
            interactive: true;
            smooth: true
            //翻页换行动画
            Behavior on contentY
            {
                NumberAnimation{ duration: 300 }
            }
            Text
            {
                id             : message
                color          : "white"
                width          : view.width
                smooth         : true
                wrapMode       : Text.WrapAnywhere
                lineHeight     : view.height * 0.05
                font.pixelSize : lineHeight * 0.7
                lineHeightMode : Text.FixedHeight
                clip           : true
                textFormat     : Text.RichText
            }
        }
        Item
        {
            width   : parent.width
            height  : parent.height * 0.01
        }
        Row
        {
            width   : parent.width
            height  : parent.height * 0.08
            Rectangle
            {
                width  : parent.width   * 0.8
                height : parent.height
                color  : "black"
                border.color: "grey"
                border.width: 1
                TextField
                {
                    id : input
                    width  : parent.width
                    height : parent.height
                    padding: 3
                    color  : "blue"
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    font.pixelSize: height * 0.4
                    onAccepted:
                    {
                        cli.sendServerData(input.text);
                        input.text = "";
                    }
                }
            }


            Button
            {
                width   : parent.width  * 0.2
                height  : parent.height
                text    : "发送"
                enabled : isCon && text.length
                focusPolicy : Qt.NoFocus
                padding : 3
                onClicked:
                {
                    cli.sendServerData(input.text);
                    input.text = "";
                }
            }
        }
        Button
        {
            width   : parent.width
            height  : parent.height * 0.08
            text    : "连接"
            enabled : !isCon
            focusPolicy : Qt.NoFocus
            padding : 3
            onClicked :
            {
                //取反
                isCon = !isCon;
                //链接服务器
                cli.startConnectServer();
                //设置焦点
                input.focus = true
            }
        }
    }
}
