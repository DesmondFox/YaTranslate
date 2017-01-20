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
    QString getNameOfLang(const QString &ui);

private:
    QString apiKey;
    QString apiVer;
    QString uiLang;
    QMap<QString, QString> langMap;

private slots:

signals:
    void error(int code, QString message);
    // В сигнале есть параметр langTo на случай, если у нас не
    void translate(QString translate, QString langFrom);

public slots:
    void getText(QString text, QString langFrom_name, QString langTo_name);
};

#endif // TRANSLATOR_H
