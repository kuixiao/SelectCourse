#include "modifyclassinfo.h"
#include "ui_modifyclassinfo.h"
#include <QDebug>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>
#include <QByteArray>
#include <QNetworkRequest>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QHttpMultiPart>

#include "jsontools.h"

ModifyClassInfo::ModifyClassInfo(int identity, QStringList classinfo, QString token, QString userID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyClassInfo)
{
    qDebug()<<"进入课堂信息修改界面"<<endl;
    m_classInfo = classinfo;
    m_token = token;
    m_userID = userID;
    m_identity = identity;
    ui->setupUi(this);
    ui->CaddressEdit->setText(m_classInfo.Caddress);
    ui->CcreditEdit->setText(m_classInfo.Ccredit);
    ui->CdeptEdit->setText(m_classInfo.Cdept);
    ui->ChourEdit->setText(m_classInfo.Chour);
    ui->CnameEdit->setText(m_classInfo.Cname);
    ui->CnumberEdit->setText(m_classInfo.Cnumber);
    ui->CsessionEdit->setText(m_classInfo.Csession);
    ui->CtimeEdit->setText(m_classInfo.Ctime);
    ui->CtypeEdit->setText(m_classInfo.Ctype);
    ui->CsumEdit->setText(QString::number(m_classInfo.Csum));
    connect(ui->commitBtn, SIGNAL(clicked()), this, SLOT(modifyClass()));
    connect(ui->returnBtn, SIGNAL(clicked()), this, SLOT(returnHome()));
}

ModifyClassInfo::~ModifyClassInfo()
{
    delete ui;
}

//判断是否存在空信息项
bool ModifyClassInfo::EmpthEdit()
{
    if (ui->CtimeEdit->text().isEmpty())return false;
    if (ui->CsessionEdit->text().isEmpty())return false;
    if (ui->CsumEdit->text().isEmpty()) return false;
    if (ui->CaddressEdit->text().isEmpty()) return false;
    return true;

}

//修改课堂信息按钮槽函数
void ModifyClassInfo::modifyClass()
{
    qDebug()<<"修改课堂信息按钮槽函数"<<endl;
    m_classInfo.Csession = ui->CsessionEdit->text().trimmed();
    m_classInfo.Csum = ui->CsumEdit->text().trimmed().toInt();
    m_classInfo.Caddress = ui->CaddressEdit->text().trimmed();
    m_classInfo.Ctime = ui->CtimeEdit->text().trimmed();

    QJsonObject json;
    json.insert("Cnumber", m_classInfo.Cnumber);
    json.insert("Csession", m_classInfo.Csession);
    json.insert("Csum", m_classInfo.Csum);
    json.insert("Caddress", m_classInfo.Caddress);
    json.insert("Ctime", m_classInfo.Ctime);
    QString urlStr;
    if (m_identity == 1)
        urlStr = "http://127.0.0.1:8080/api/teacher/update/classinfo/" + m_userID;
    else if (m_identity == 2)
    {
        urlStr = "http://127.0.0.1:8080/api/dean/update/classinfo/" + m_userID;
    }
    else
    {
        return;
    }
    QUrl url(urlStr);
    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    qDebug()<<"设置json头"<<endl;
    QNetworkRequest request = JsonTools::getJsonHeader(m_token,url);// 构造请求
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    manager->put(request, dataArray); // 发送请求
    qDebug()<<"请求已发送"<<endl;
}

//修改课堂信息响应槽函数
void ModifyClassInfo::replyFinished(QNetworkReply *reply)
{
    JsonTools::replyFinished(reply);
}

//返回上一个界面
void ModifyClassInfo::returnHome()
{
    this->close();
}
