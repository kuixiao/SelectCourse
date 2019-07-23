#include "jsontools.h"
#include <QUrl>
#include <QByteArray>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QHttpMultiPart>
#include <QObject>

void JsonTools::getPutJson(QString m_token,QByteArray &dataArray,QNetworkRequest &request)
{
    QJsonObject json;
    json.insert("Tpassword", "222");

    QUrl url("http://127.0.0.1:8080/api/update/000002");
    QJsonDocument document;
    document.setObject(json);
    dataArray = document.toJson(QJsonDocument::Compact);

    // 构造请求
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", m_token.toLatin1());
    request.setUrl(url);
}

//构造Json头部
QNetworkRequest JsonTools::getJsonHeader(QString m_token,QUrl url)
{
    QNetworkRequest request;
    // 构造请求
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", m_token.toLatin1());
    request.setUrl(url);
    return request;
}

//解析POST & PUT方法返回的Json数据
void JsonTools::replyFinished(QNetworkReply *reply)
{
    // 获取响应信息
    QByteArray bytes = reply->readAll();

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(bytes, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << QStringLiteral("解析Json失败");
        return;
    }

    // 解析Json
    if (doucment.isObject()) {
        QJsonObject obj = doucment.object();
        QJsonValue value;
        if (obj.contains("code")) {
            value = obj.take("code");
            if (value.isString()) {
                QString data = value.toString();
                qDebug() << data;
            }
        }
        if (obj.contains("msg")) {
            value = obj.take("msg");
            if (value.isString()) {
                const QString data = value.toString();

                QMessageBox::information(nullptr,"result:",data);
                qDebug() << data;
            }
        }
    }
}

//解析GET请求返回的Json数据 返回["data"]数据
QJsonValue JsonTools::getDataOfGet(QNetworkReply *reply)
{
    qDebug()<<"解析Json"<<endl;
    QJsonValue emptyForReturn;
    // 获取响应信息
    QByteArray bytes = reply->readAll();
    qDebug()<<"recv:"<<bytes<<endl;
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(bytes, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        QMessageBox::information(nullptr,"result:","解析Json失败");
        return emptyForReturn;
    }

    // 解析Json
    if (doucment.isObject())
    {
        QJsonObject obj = doucment.object();
        if ( !obj.contains("code") || !obj.contains("msg") || !obj.contains("data"))
        {
            QMessageBox::information(nullptr,"result:","错误的Json格式");
            return emptyForReturn;
        }
        QJsonValue value[3];
        value[0] = obj.take("code");
        value[1] = obj.take("msg");
        qDebug()<<"msg:"<<value[1].toString()<<endl;
        value[2] = obj.take("data");
        return value[2];
    }
    else
    {
        QMessageBox::warning(nullptr,"login result:","错误的Json格式 isObject return false");
    }
    return emptyForReturn;
}

