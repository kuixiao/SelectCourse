#include "modifypersonalinfo.h"
#include "ui_modifypersonalinfo.h"

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

ModifyPersonalInfo::ModifyPersonalInfo(int identity, studentInfo stu, QDialog *parent) :
    QDialog(parent), ui(new Ui::modifyPersonalInfo)
{
    ui->setupUi(this);
    m_student = stu;
    m_token = stu.Token;
    m_identity = identity;
    getUserInfo();
    connect(ui->modifyBtn, SIGNAL(clicked()), this, SLOT(modifyInfo()));
    connect(ui->returnBtn, SIGNAL(clicked()), this, SLOT(returnLastUI()));
}

ModifyPersonalInfo::ModifyPersonalInfo(int identity,teacherInfo tea,QDialog *parent) :
    QDialog(parent), ui(new Ui::modifyPersonalInfo)
{
    ui->setupUi(this);
    ui->userIDLabel->setText("老师编号");
    ui->majorLabel->setText("院系");
    ui->classLabel->setText("职称");
    m_teacher = tea;
    m_token = tea.Token;
    m_identity = identity;
    getUserInfo();
    connect(ui->modifyBtn, SIGNAL(clicked()), this, SLOT(modifyInfo()));
    connect(ui->returnBtn, SIGNAL(clicked()), this, SLOT(returnLastUI()));
}

ModifyPersonalInfo::ModifyPersonalInfo(int identity, deanInfo dean, QDialog *parent) :
    QDialog(parent), ui(new Ui::modifyPersonalInfo)
{
    ui->setupUi(this);
    ui->userIDLabel->setText("系主任编号");
    ui->majorLabel->setText("院系");
    ui->classLabel->setText("职称");
    m_dean = dean;
    m_token = dean.Token;
    m_identity = identity;
    getUserInfo();
    connect(ui->modifyBtn, SIGNAL(clicked()), this, SLOT(modifyInfo()));
    connect(ui->returnBtn, SIGNAL(clicked()), this, SLOT(returnLastUI()));
}

ModifyPersonalInfo::~ModifyPersonalInfo()
{
    delete ui;
}

// 获取用户信息 并显示在UI上
void ModifyPersonalInfo::getUserInfo()
{
    if (m_identity == 0 || m_identity == 3)
    {
        //studentInfo m_student;
        ui->birthdayEdit->setText(m_student.Sbirthday);
        ui->classEdit->setText(m_student.Sclass);
        ui->majorEdit->setText(m_student.Smajor);
        ui->userIDEdit->setText(m_student.Sno);
        ui->phoneEdit->setText(m_student.Sphone);
        ui->nameEdit->setText(m_student.Sname);
        ui->sexBox->setItemText(0,m_student.Ssex);
        if (m_student.Ssex == "男")ui->sexBox->setCurrentIndex(0);
        else if (m_student.Ssex == "女")ui->sexBox->setCurrentIndex(1);
        ui->userIDEdit->setReadOnly(true);
    }
    else if (m_identity == 1 || m_identity == 4)
    {
        ui->birthdayEdit->setText(m_teacher.Tbirthday);
        ui->classEdit->setText(m_teacher.Tclass);
        ui->majorEdit->setText(m_teacher.Tmajor);
        ui->userIDEdit->setText(m_teacher.Tno);
        ui->phoneEdit->setText(m_teacher.Tphone);
        ui->nameEdit->setText(m_teacher.Tname);
        ui->sexBox->setItemText(0,m_teacher.Tsex);
        if (m_teacher.Tsex == "男")ui->sexBox->setCurrentIndex(0);
        else if (m_teacher.Tsex == "女")ui->sexBox->setCurrentIndex(1);
        ui->userIDEdit->setReadOnly(true);
    }
    else if (m_identity == 2)
    {
        ui->birthdayEdit->setText(m_dean.Dbirthday);
        ui->classEdit->setText(m_dean.Dclass);
        ui->majorEdit->setText(m_dean.Dmajor);
        ui->userIDEdit->setText(m_dean.Dno);
        ui->phoneEdit->setText(m_dean.Dphone);
        ui->nameEdit->setText(m_dean.Dname);
        ui->sexBox->setItemText(0,m_dean.Dsex);
        if (m_dean.Dsex == "男")ui->sexBox->setCurrentIndex(0);
        else if (m_dean.Dsex == "女")ui->sexBox->setCurrentIndex(1);
        ui->userIDEdit->setReadOnly(true);
    }

}

//判断信息项是否存在空项
bool ModifyPersonalInfo::EmptyInfomation()
{
    if (ui->userIDEdit->text().isEmpty())return false;
    if (ui->nameEdit->text().isEmpty())return false;
    if (ui->majorEdit->text().isEmpty())return false;
    if (ui->classEdit->text().isEmpty())return false;
    if (ui->phoneEdit->text().isEmpty())return false;
    if (ui->birthdayEdit->text().isEmpty())return false;
    return true;
}

//修改个人信息按钮槽函数
void ModifyPersonalInfo::modifyInfo()
{
    if (!EmptyInfomation())  //判断是否存在未填信息项
    {
        QMessageBox::warning(this, "warning","请填写必填信息项");
        return;
    }
    QJsonObject json = putJsonBody();   //构造json的Body
    QString urlStr;
    if (m_identity == 0)
    {
        urlStr = "http://127.0.0.1:8080/api/student/update/student/";
    }
    else if (m_identity == 1)
    {
        urlStr = "http://127.0.0.1:8080/api/teacher/update/teacher/";
    }
    else if (m_identity == 2)
    {
        urlStr = "http://127.0.0.1:8080/api/dean/update/dean/";
    }
    else if (m_identity == 3)
    {
        urlStr = "http://127.0.0.1:8080/api/dean/update/student/";
    }
    else if (m_identity == 4)
    {
        urlStr = "http://127.0.0.1:8080/api/dean/update/teacher/";
    }
    else
    {
        return;
    }
    QUrl url(urlStr + ui->userIDEdit->text().trimmed());
    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    // 构造请求
    QNetworkRequest request = JsonTools::getJsonHeader(m_token,url);


    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // 连接信号槽
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    // 发送请求
    manager->put(request, dataArray);
}

//修改个人信息响应槽函数
void ModifyPersonalInfo::replyFinished(QNetworkReply *reply)
{
    JsonTools::replyFinished(reply);
}

//返回用户主界面
void ModifyPersonalInfo::returnLastUI()
{
    this->close();
}

//修改用户信息构造json的Body
QJsonObject ModifyPersonalInfo::putJsonBody()
{
    QJsonObject json;
    QJsonObject emptyJson;
    if (m_identity == 0 || m_identity == 3)
    {
        json.insert("Sno", ui->userIDEdit->text().trimmed());           //学号
        json.insert("Smajor", ui->majorEdit->text().trimmed());         //专业
        json.insert("Sname", ui->nameEdit->text().trimmed());           //名字
        json.insert("Ssex", ui->sexBox->currentText().trimmed());       //性别
        json.insert("Sbirthday", ui->birthdayEdit->text().trimmed());   //出生日期
        json.insert("Sclass", ui->classEdit->text().trimmed());         //班级
        json.insert("Sphone", ui->phoneEdit->text().trimmed());         //电话
    }
    else if (m_identity == 1 || m_identity == 4)
    {
        json.insert("Tno", ui->userIDEdit->text().trimmed());           //教师职工编号
        json.insert("Tdept", ui->majorEdit->text().trimmed());          //教师所属院系
        json.insert("Tname", ui->nameEdit->text().trimmed());           //教师姓名
        json.insert("Tsex", ui->sexBox->currentText().trimmed());       //教师性别
        json.insert("Tbirthday", ui->birthdayEdit->text().trimmed());   //教师出生日期
        json.insert("Tphone", ui->phoneEdit->text().trimmed());         //教师联系电话
        json.insert("Tclass", ui->classEdit->text().trimmed());         //教师职称信息
    }
    else if (m_identity == 2)
    {
        json.insert("Dno", ui->userIDEdit->text().trimmed());           //系主任职工编号
        json.insert("Ddept", ui->majorEdit->text().trimmed());          //系主任所属院系
        json.insert("Dname", ui->nameEdit->text().trimmed());           //系主任姓名
        json.insert("Dsex", ui->sexBox->currentText().trimmed());       //系主任性别
        json.insert("Dbirthday", ui->birthdayEdit->text().trimmed());   //系主任出生日期
        json.insert("Dphone", ui->phoneEdit->text().trimmed());         //系主任联系电话
        json.insert("Dclass", ui->classEdit->text().trimmed());       //系主任职称信息
    }
    else
    {
        QMessageBox::warning(this, "warning","the identity is incorrect! It is " + QString::number(m_identity));
        return emptyJson;
    }
    return json;
}


