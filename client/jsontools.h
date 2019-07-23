#ifndef JSONTOOLS_H
#define JSONTOOLS_H
#include <QUrl>
#include <QByteArray>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
#include <QHttpMultiPart>


class JsonTools
{
public:
    static void getPutJson(QString m_token, QByteArray &dataArray, QNetworkRequest &request);
    static void replyFinished(QNetworkReply *reply);
    static QNetworkRequest getJsonHeader(QString m_token,QUrl url);
    static QJsonValue getDataOfGet(QNetworkReply *reply);
};
#endif // JSONTOOLS_H
