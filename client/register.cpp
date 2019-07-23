#include "register.h"
#include "ui_register.h"
#include <QDebug>
#include <QMessageBox>
#include <QUrl>
#include <QByteArray>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>

#include "jsontools.h"



Register::Register(int identity, QWidget *parent) :
    QDialog(parent), ui(new Ui::Register)
{
    ui->setupUi(this);
    m_identity = identity;
    ui->phoneEdit->setPlaceholderText("请输入联系方式信息");
    ui->passwordEdit1->setPlaceholderText("请输入密码");
    ui->passwordEdit2->setPlaceholderText("请再次输入密码");

    if (m_identity == 0)  //学生注册
    {
        ui->userIDEdit->setPlaceholderText("请输入学号信息");
        ui->majorEdit->setPlaceholderText("请输入专业信息");
        ui->classEdit->setPlaceholderText("请输入班级信息");
    }
    else if (m_identity == 1 || m_identity == 2) //系主任 教师注册
    {
        ui->userIDEdit->setPlaceholderText("请输入教师职工编号");
        ui->majorEdit->setPlaceholderText("请输入院系信息");
        ui->classEdit->setPlaceholderText("请输入职称信息信息");
    }
    /*else if (m_identity == 2) //系主任注册
    {
        ui->userIDEdit->setPlaceholderText("请输入职工编号");
        ui->majorEdit->setPlaceholderText("请输入院系信息");
    }*/

    connect(ui->registerBtn, SIGNAL(clicked()), this, SLOT(registerCommit()));
    connect(ui->returnBtn, SIGNAL(clicked()), this, SLOT(returnLoginUI()));
}

Register::~Register()
{
    delete ui;
}

void Register::returnLoginUI()
{
    this->close();
}

bool Register::EmptyInfomation()
{
    if (ui->userIDEdit->text().isEmpty())return false;
    if (ui->nameEdit->text().isEmpty())return false;
    if (ui->majorEdit->text().isEmpty())return false;
    if (ui->classEdit->text().isEmpty())return false;
    if (ui->phoneEdit->text().isEmpty())return false;
    if (ui->passwordEdit1->text().isEmpty())return false;
    if (ui->passwordEdit2->text().isEmpty())return false;
    return true;
}

void Register::registerCommit()
{
    if (!EmptyInfomation())  //判断是否存在未填信息项
    {
        QMessageBox::warning(this, "warning","please input the information needed");
        return;
    }
    if (ui->passwordEdit1->text() != ui->passwordEdit2->text()) //判断两次输入密码是否一致
    {
        QMessageBox::warning(this, "warning","the password is not same as the another!");
        return;
    }

    QJsonObject json;
    QString m_identityStr;
    json.insert("Spassword", ui->passwordEdit1->text().trimmed());//密码
    if (m_identity == 0)
    {
        m_identityStr = "student";
        json.insert("Sno", ui->userIDEdit->text().trimmed());           //学号
        json.insert("Smajor", ui->majorEdit->text().trimmed());         //专业
        json.insert("Sname", ui->nameEdit->text().trimmed());           //名字
        json.insert("Ssex", ui->sexBox->currentText().trimmed());       //性别
        json.insert("Sbirthday", ui->birthdayEdit->text().trimmed());   //出生日期
        json.insert("Sclass", ui->classEdit->text().trimmed());         //班级
        json.insert("Sphone", ui->phoneEdit->text().trimmed());         //电话
    }
    else if (m_identity == 1)
    {
        m_identityStr = "teacher";
        json.insert("Tno", ui->userIDEdit->text().trimmed());           //教师职工编号
        json.insert("Tdept", ui->majorEdit->text().trimmed());          //教师所属院系
        json.insert("Tname", ui->nameEdit->text().trimmed());           //教师姓名
        json.insert("Tsex", ui->sexBox->currentText().trimmed());       //教师性别
        json.insert("Tbirthday", ui->birthdayEdit->text().trimmed());   //教师出生日期
        json.insert("Tphone", ui->phoneEdit->text().trimmed());         //教师联系电话
        json.insert("Tclass", ui->classEdit->text().trimmed());       //教师职称信息
    }
    else if (m_identity == 2)
    {
        m_identityStr = "dean";
        json.insert("Dno", ui->userIDEdit->text().trimmed());           //系主任职工编号
        json.insert("Ddept", ui->majorEdit->text().trimmed());          //系主任所属院系
        json.insert("Dname", ui->nameEdit->text().trimmed());           //系主任姓名
        json.insert("Dsex", ui->sexBox->currentText().trimmed());       //系主任性别
        json.insert("Dbirthday", ui->birthdayEdit->text().trimmed());   //系主任出生日期
        json.insert("Dphone", ui->phoneEdit->text().trimmed());         //系主任联系电话
        json.insert("Dclass", ui->classEdit->text().trimmed());         //系主任职称信息
    }
    else
    {
        QMessageBox::warning(this, "warning","the m_identity is incorrect! It is " + QString::number(m_identity));
        return ;
    }
    QUrl url("http://127.0.0.1:8080/api/register/" + m_identityStr);

    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    // 构造请求
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setUrl(url);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // 连接信号槽
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));

    // 发送请求
    manager->post(request, dataArray);
}

/*
 * @brief: analyse json-data from returnJson
 */
void Register::replyFinished(QNetworkReply *reply)
{
    JsonTools::replyFinished(reply);
}


