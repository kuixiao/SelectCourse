#include "modifypassword.h"
#include "ui_modifypassword.h"
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

#include "jsontools.h"

extern int identity;

ModifyPassword::ModifyPassword(QString token, QString userID,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyPassword)
{
    ui->setupUi(this);
    m_token = token;
    m_userID = userID;
    connect(ui->commitBtn, SIGNAL(clicked()), this, SLOT(updatePwd()));
    connect(ui->returnBtn, SIGNAL(clicked()), this, SLOT(returnHome()));
}

ModifyPassword::~ModifyPassword()
{
    delete ui;
}

// 修改密码提交按钮槽函数
void ModifyPassword::updatePwd()
{
    QString oldPwd = ui->lineEdit->text();
    QString newPwd = ui->lineEdit_2->text();
    QString newPwd2 = ui->lineEdit_3->text();
    if (oldPwd.isEmpty() || newPwd.isEmpty() || newPwd2.isEmpty())
    {
        QMessageBox::warning(this, "warning", "输入不能为空");
        return;
    }
    if (newPwd != newPwd2)
    {
        QMessageBox::warning(this, "warning", "两次输入密码不一致");
        return;
    }

    QJsonObject json;
    /*if (identity == 0)
    {
        json.insert("Spassword", newPwd);
    }
    if (identity == 1)
    {
        json.insert("Tpassword", newPwd);
    }
    if (identity == 2)
    {
        json.insert("Dpassword", newPwd);
    }*/
    json.insert("Pwd", newPwd);
    QUrl url("http://127.0.0.1:8080/api/update/password/" + m_userID + "/"+QString::number(identity));
    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    QNetworkRequest request = JsonTools::getJsonHeader(m_token,url);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    manager->put(request, dataArray);
}

//返回上一界面
void ModifyPassword::returnHome()
{
    this->close();
}

//修改密码响应槽函数
void ModifyPassword::replyFinished(QNetworkReply *reply)
{
    JsonTools::replyFinished(reply);
}

