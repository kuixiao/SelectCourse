#include "course.h"
#include "ui_course.h"

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



extern QStringList itemInfo;

Course::Course(QString token, QString userID, int op, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Course)
{
    m_token = token;
    m_userID = userID;
    m_op = op;
    ui->setupUi(this);
    initUI();
    connect(ui->returnBtn, SIGNAL(clicked()), this, SLOT(returnHome()));

}

Course::~Course()
{
    delete ui;
}

void Course::initUI()
{
    if (m_op == 0)
    {
        delete ui->horizontalLayout_7;
        ui->titleLabel->setText("增加课程");
        connect(ui->commitBtn, SIGNAL(clicked()), this, SLOT(addCourse()));
    }
    else if (m_op == 1)
    {
        ui->titleLabel->setText("修改课程");
        ui->CnoEdit->setText(itemInfo.at(0));
        ui->CnameEdit->setText(itemInfo.at(1));
        ui->CcreditEdit->setText(itemInfo.at(2));
        ui->ChourEdit->setText(itemInfo.at(3));
        ui->CtypeEdit->setText(itemInfo.at(4));
        ui->CdeptEdit->setText(itemInfo.at(5));
        connect(ui->commitBtn, SIGNAL(clicked()), this, SLOT(modifyCourse()));
    }
    else if (m_op == 2)
    {
        ui->titleLabel->setText("删除课程");
    }
    else if (m_op == 3)
    {
        ui->titleLabel->setText("增加课程");
    }
}

bool Course::EmptyLineEdit()
{
    //if (ui->CnoEdit->text().isEmpty())return false;
    if (ui->CnameEdit->text().isEmpty())return false;
    if (ui->CcreditEdit->text().isEmpty())return false;
    if (ui->ChourEdit->text().isEmpty())return false;
    if (ui->CtypeEdit->text().isEmpty())return false;
    if (ui->CdeptEdit->text().isEmpty())return false;
    return true;
}

void Course::addCourse()
{
    if (!EmptyLineEdit())  //判断是否存在未填信息项
    {
        QMessageBox::warning(this, "warning","信息不能为空");
        return;
    }

    QJsonObject json;
    json.insert("Cname", ui->CnameEdit->text().trimmed());
    json.insert("Ccredit", ui->CcreditEdit->text().trimmed().toFloat());
    json.insert("Chour", ui->ChourEdit->text().trimmed().toInt());
    json.insert("Ctype", ui->CtypeEdit->text().trimmed());
    json.insert("Cdept", ui->CdeptEdit->text().trimmed());
    QUrl url("http://127.0.0.1:8080/api/dean/add/course/" + m_userID);

    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);
    QNetworkRequest request = JsonTools::getJsonHeader(m_token, url);// 构造请求
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    // 发送请求
    manager->post(request, dataArray);
}

//修改课程信息
void Course::modifyCourse()
{
    if (!EmptyLineEdit())  //判断是否存在未填信息项
    {
        QMessageBox::warning(this, "warning","信息不能为空");
        return;
    }

    QJsonObject json;
    json.insert("Cno", ui->CnoEdit->text().trimmed());
    json.insert("Cname", ui->CnameEdit->text().trimmed());
    json.insert("Ccredit", ui->CcreditEdit->text().trimmed().toFloat());
    json.insert("Chour", ui->ChourEdit->text().trimmed().toInt());
    json.insert("Ctype", ui->CtypeEdit->text().trimmed());
    json.insert("Cdept", ui->CdeptEdit->text().trimmed());
    QUrl url("http://127.0.0.1:8080/api/dean/update/course/" + m_userID);

    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);
    QNetworkRequest request = JsonTools::getJsonHeader(m_token, url);// 构造请求
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    // 发送请求
    manager->put(request, dataArray);
}




void Course::replyFinished(QNetworkReply *reply)
{
    JsonTools::replyFinished(reply);
}

//返回上一个界面
void Course::returnHome()
{
    this->close();
}
