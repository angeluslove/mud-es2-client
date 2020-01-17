#ifndef COLOR_H
#define COLOR_H

#include <QObject>
#include <QHash>
#include <QByteArray>

class color : public QObject
{
    Q_OBJECT
public:
    explicit color(QObject *parent = nullptr);

    QString cheackColor(QByteArray data);

signals:

private:
    QByteArray esc;

    QHash<QByteArray,QByteArray> m_color;

public slots:

};

#endif // COLOR_H
