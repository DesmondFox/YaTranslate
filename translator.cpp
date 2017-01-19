#include "translator.h"

Translator::Translator(const QString &key, QObject *parent) : QObject(parent)
{
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

    QEventLoop  loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        qDebug() << QString::fromUtf8(reply->readAll());
    }


}
