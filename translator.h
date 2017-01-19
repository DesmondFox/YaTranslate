#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QtNetwork>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

class Translator : public QObject
{
    Q_OBJECT
public:
    explicit Translator(const QString &key, QObject *parent = 0);
    void getLangList();
    void setUI(QString ui);
    QStringList langList();

private:
    QString apiKey;
    QString apiVer;
    QString uiLang;
    QMap<QString, QString> langMap;

private slots:

signals:
    void error(int code, QString message);

public slots:
};

#endif // TRANSLATOR_H
