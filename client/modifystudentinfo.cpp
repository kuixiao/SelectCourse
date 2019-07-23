#include "modifystudentinfo.h"
#include "ui_modifystudentinfo.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>

extern int identity;

ModifyStudentInfo::ModifyStudentInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyStudentInfo)
{
    ui->setupUi(this);
    if (identity == 0)
    {
        ui->userIDLabel->setText("学号");
        ui->classLabel->setText("班级");
        ui->majorLabel->setText("专业");

        ui->userIDEdit->setPlaceholderText("请输入学号信息");
        ui->majorEdit->setPlaceholderText("请输入专业信息");
        ui->classEdit->setPlaceholderText("请输入班级信息");
    }
    else if (identity == 1 || identity == 2)
    {
        ui->userIDLabel->setText("职工编号");
        ui->classLabel->setText("职称");
        ui->majorLabel->setText("院系");
        ui->userIDEdit->setPlaceholderText("请输入教师职工编号");
        ui->majorEdit->setPlaceholderText("请输入院系信息");
        ui->classEdit->setPlaceholderText("请输入职称信息信息");
    }
    getUserInfo();
    connect(ui->modifyBtn, SIGNAL(clicked()), this, SLOT(modifyInfo()));
    connect(ui->returnBtn, SIGNAL(clicked()), this, SLOT(returnLastUI()));
}

ModifyStudentInfo::~ModifyStudentInfo()
{
    delete ui;
}

// 获取用户信息 并显示在UI上
void ModifyStudentInfo::getUserInfo()
{
    if (identity == 0)
    {
        ui->birthdayEdit->setText(StudentHome::m_student.Sbirthday);
        ui->classEdit->setText(StudentHome::m_student.Sclass);
        ui->majorEdit->setText(StudentHome::m_student.Smajor);
        ui->userIDEdit->setText(StudentHome::m_student.Sno);
        ui->phoneEdit->setText(StudentHome::m_student.Sphone);
        ui->nameEdit->setText(StudentHome::m_student.Sname);
        ui->sexBox->setItemText(0,StudentHome::m_student.Ssex);
        if (StudentHome::m_student.Ssex == "男")ui->sexBox->setCurrentIndex(0);
        else if (StudentHome::m_student.Ssex == "女")ui->sexBox->setCurrentIndex(1);
        ui->userIDEdit->setReadOnly(true);
    }
    else if (identity == 1)
    {

    }
    else if (identity == 2)
    {

    }

//    m_StudentHome::m_student.Sno = userInfo.Sno;
//    m_StudentHome::m_student.Sname = userInfo.Sname;
//    m_StudentHome::m_student.Smajor = userInfo.Smajor;
//    m_StudentHome::m_student.Sphone = userInfo.Sphone;
//    m_StudentHome::m_student.Ssex = userInfo.Ssex;
//    m_StudentHome::m_student.Token = userInfo.Token;
//    m_StudentHome::m_student.Sbirthday = userInfo.Sbirthday;
//    m_StudentHome::m_student.Sclass = userInfo.Sclass;
}

//判断信息项是否存在空项
bool ModifyStudentInfo::EmptyInfomation()
{
    if (ui->userIDEdit->text().isEmpty())return false;
    if (ui->nameEdit->text().isEmpty())return false;
    if (ui->majorEdit->text().isEmpty())return false;
    if (ui->classEdit->text().isEmpty())return false;
    if (ui->phoneEdit->text().isEmpty())return false;
    if (ui->birthdayEdit->text().isEmpty())return false;
    return true;
}

void ModifyStudentInfo::modifyInfo()
{
    if (!EmptyInfomation())  //判断是否存在未填信息项
    {
        QMessageBox::warning(this, "warning","请填写必填信息项");
        return;
    }

    QJsonObject json;
    QString identityStr;
    json.insert("Spassword", ui->passwordEdit1->text().trimmed());//密码
    if (identity == 0)
    {
        identityStr = "student";
        json.insert("Sno", ui->userIDEdit->text().trimmed());           //学号
        json.insert("Smajor", ui->majorEdit->text().trimmed());         //专业
        json.insert("Sname", ui->nameEdit->text().trimmed());           //名字
        json.insert("Ssex", ui->sexBox->currentText().trimmed());       //性别
        json.insert("Sbirthday", ui->birthdayEdit->text().trimmed());   //出生日期
        json.insert("Sclass", ui->classEdit->text().trimmed());         //班级
        //json.insert("Sphone", ui->phoneEdit->text().trimmed());       //电话
    }
    else if (identity == 1)
    {
        identityStr = "teacher";
        json.insert("Tno", ui->userIDEdit->text().trimmed());           //教师职工编号
        json.insert("Tdept", ui->majorEdit->text().trimmed());          //教师所属院系
        json.insert("Tname", ui->nameEdit->text().trimmed());           //教师姓名
        json.insert("Tsex", ui->sexBox->currentText().trimmed());       //教师性别
        json.insert("Tbirthday", ui->birthdayEdit->text().trimmed());   //教师出生日期
        json.insert("Tphone", ui->phoneEdit->text().trimmed());         //教师联系电话
        //json.insert("Tclass", ui->phoneEdit->text().trimmed());       //教师职称信息
    }
    else if (identity == 2)
    {
        identityStr = "dean";
        json.insert("Tno", ui->userIDEdit->text().trimmed());           //系主任职工编号
        json.insert("Tdept", ui->majorEdit->text().trimmed());          //系主任所属院系
        json.insert("Tname", ui->nameEdit->text().trimmed());           //系主任姓名
        json.insert("Tsex", ui->sexBox->currentText().trimmed());       //系主任性别
        json.insert("Tbirthday", ui->birthdayEdit->text().trimmed());   //系主任出生日期
        json.insert("Tphone", ui->phoneEdit->text().trimmed());         //系主任联系电话
        //json.insert("Tclass", ui->phoneEdit->text().trimmed());       //系主任职称信息
    }
    else
    {
        QMessageBox::warning(this, "warning","the identity is incorrect! It is " + QString::number(identity));
        return ;
    }
    QUrl url("http://127.0.0.1:8080/api/update/" + StudentHome::m_student.Sno);

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
void ModifyStudentInfo::returnLastUI()
{

}
