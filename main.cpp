#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "mytcpsocket.h"


int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    myTcpSocket client;
    engine.rootContext()->setContextProperty("cli",&client);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }
    //加载初始化函数
    QObject* root = engine.rootObjects().first();
    QMetaObject::invokeMethod(root,"init");

    return app.exec();
}
