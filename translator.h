#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QtNetwork>
#include <QDebug>

class Translator : public QObject
{
    Q_OBJECT
public:
    explicit Translator(const QString &key, QObject *parent = 0);
    void getLangList();
    void setUI(QString ui);

private:
    QString apiKey;
    QString apiVer;
    QString uiLang;
    QMap<QString, QString> langMap;

private slots:

signals:

public slots:
};

#endif // TRANSLATOR_H
