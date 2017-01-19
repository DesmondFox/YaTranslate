#include "translator.h"

Translator::Translator(const QString &key, QObject *parent) : QObject(parent)
{
    qDebug() << "load";
    apiKey  = key;
    apiVer  = "v1.5";
    uiLang  = "ru";     // TODO: Изменять в зависимости от locale
}

void Translator::setUI(QString ui)
{
    uiLang  = ui;
}

void Translator::getLangList()
{
    QUrl requestUrl("https://translate.yandex.net/api/v1.5/tr.json/getLangs");
    QUrlQuery query;
    query.addQueryItem("key",   apiKey);
    query.addQueryItem("ui",    uiLang);
    requestUrl.setQuery(query);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(requestUrl);
    QNetworkReply   *reply = manager->get(request);

    // Чтобы не надо было создавать отдельный слот
    QEventLoop  loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    // Если ошибок в запросе нет
    if (reply->error() == QNetworkReply::NoError)
    {
        // Парсим наш ответ
        QJsonDocument   document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject     err      = document.object().value("code").toObject();
        // Если в ответе нет кода ошибки
        if (err.isEmpty())
        {
            QJsonObject lang     = document.object().value("langs").toObject();
            foreach (QString value, lang.keys())
            {
                QString description  = lang[value].toString();
                langMap[description] = value;
            }
            qDebug() << "Dictionary loaded";
        }
        else
        {
            // TODO: Сделать обработку ошибок

        }
    }
}

QStringList Translator::langList()
{
    QStringList list;
    foreach (QString value, langMap)
    {
        list.append(langMap.key(value));
    }
    qDebug() << list;
    return list;
}
