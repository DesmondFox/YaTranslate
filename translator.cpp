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
    QUrl requestUrl("https://translate.yandex.net/api/"+apiVer+"/tr.json/getLangs");
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
            qDebug() << "err";
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
    qDebug() << "List created";
    return list;
}

QString Translator::getNameOfLang(const QString &ui)
{
    return langMap.key(ui);
}

void Translator::getText(QString text, QString langFrom_name, QString langTo_name)
{
    QString langFrom = langMap[langFrom_name];
    QString langTo   = langMap[langTo_name];

    QUrl requestUrl("https://translate.yandex.net/api/"+apiVer+"/tr.json/translate");
    QUrlQuery query;
    query.addQueryItem("key", apiKey);
    query.addQueryItem("text", text);
    query.addQueryItem("lang", langFrom+"-"+langTo);
    query.addQueryItem("format", "html");

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(requestUrl);
    request.setHeader(QNetworkRequest::UserAgentHeader, QVariant("YaTranslator/1.0"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));

    QNetworkReply   *reply = manager->post(request, query.toString().toUtf8());

    // Ожидаем ответ
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    // Парсим ответ
    QJsonDocument document  = QJsonDocument::fromJson(reply->readAll());
    QString code            = QString::number(document.object().value("code").toDouble());
    if (code == QString::number(200))
    {
        QString langFrom_Ui = langMap.key(document.object().value("lang").toString().split("-")[0]);
        QString outputText  = document.object().value("text").toArray()[0].toString();
        emit translate(outputText, langFrom_Ui);
        qDebug() << "Note:\t"<< "Translating: " << text;
    }
    else
    {
        error(code.toInt(), "Error");
        qDebug() << "Error:\t" << code;
    }

}
