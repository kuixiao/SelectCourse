#include "teacherhome.h"
#include "ui_teacherhome.h"
#include "customtabstyle.h"

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
#include <modifypassword.h>
#include <modifyclassinfo.h>
#include <jsontools.h>


extern QString Token;
extern int identity;

teacherHome::teacherHome(QString userID, QString token, QDialog *parent) :
    QDialog(parent), ui(new Ui::teacherHome)
{
    ui->setupUi(this);
    m_teacher.Identity = identity;
    m_teacher.Tno = userID;
    m_teacher.Token = token;
    ui->tabWidget->setTabText(0,"个人信息");
    ui->tabWidget->setTabText(1,"我的课堂");
    ui->tabWidget->setTabText(2,"课堂学生");
    ui->tabWidget->setTabPosition(QTabWidget::West);
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle(100, 100));

    initTable();
    getPersonalInfo();  //获取个人信息
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(getInfo(int)));
    connect(ui->modifyBtn,SIGNAL(clicked()), this, SLOT(modifyUserInfo()));
    connect(ui->modifyPwdBtn, SIGNAL(clicked()), this, SLOT(modifyPassword()));
}

teacherHome::~teacherHome()
{
    delete ui;
}

//设置表格属性
void teacherHome::initTable()
{
    //个人课堂信息表
    QStringList classheaders;
    classheaders<<"课堂编号"<<"课程名称"<<"学分"<<"学时"<<"课程类型"<<"开课院系"
          <<"上课日期"<<"课堂节次"<<"上课地点"<<"课堂人数"<<"详情"<<" ";
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(12);
    ui->tableWidget->setHorizontalHeaderLabels(classheaders);
    //表格属性设置
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列宽自适应
    ui->tableWidget->setFrameShape(QFrame::NoFrame);

    //课堂编号 学号 姓名 专业 性别 班级
    QStringList studentHeaders;
    studentHeaders<<"课堂编号"<<"学号"<<"姓名"<<"专业"<<"性别"<<"班级";
    ui->studentTable->setRowCount(0);
    ui->studentTable->setColumnCount(6);
    ui->studentTable->setHorizontalHeaderLabels(studentHeaders);
    //表格属性设置
    ui->studentTable->verticalHeader()->hide();
    ui->studentTable->horizontalHeader()->setSectionsClickable(false);
    ui->studentTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列宽自适应
    ui->studentTable->setFrameShape(QFrame::NoFrame);
}

//修改个人信息按钮槽函数
void teacherHome::modifyUserInfo()
{
    m_modifyPersonalInfo = new ModifyPersonalInfo(identity, m_teacher);
    m_modifyPersonalInfo->show();
}

//修改密码按钮槽函数
void teacherHome::modifyPassword()
{
    ModifyPassword *modifyPwd = new ModifyPassword(m_teacher.Token,m_teacher.Tno);
    modifyPwd->show();
}

//查看学生按钮槽函数
void teacherHome::queryStudentOfClass()
{
    QPushButton *button = dynamic_cast<QPushButton *>(QObject::sender());
    QModelIndex index = ui->tableWidget->indexAt(button->pos());
    int row = index.row();
    int col = index.column();
    qDebug()<<row<<" "<<col<<endl;
    QString urlStr = "http://127.0.0.1:8080/api/teacher/mystudent/";
    urlStr.append(m_teacher.Tno+"/");
    urlStr.append(ui->tableWidget->item(row, 0)->text());
    QUrl url(urlStr);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    //连接信号槽
    connect(manager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(getStudentOfClass(QNetworkReply *)));
    QNetworkRequest request = JsonTools::getJsonHeader(m_teacher.Token, url);
    manager->get(request);// 发送请求
}

//查看学生响应槽函数
void teacherHome::getStudentOfClass(QNetworkReply *reply)
{
    QJsonValue jsonData = JsonTools::getDataOfGet(reply);
    if (jsonData.isNull())
    {
        QMessageBox::warning(this,"result:","jsonData为空");
        return ;
    }
    showTableInfo(jsonData, 1);
    ui->tabWidget->setCurrentIndex(2);
}

//选项卡切换槽函数
void teacherHome::getInfo(int index)
{
    if (index == 0) //个人信息
    {
        getPersonalInfo();
    }
    else if (index == 1)    //我的课堂
    {
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);
        getClassInfo();
    }
}

//获取个人课堂信息按钮槽函数
void teacherHome::getClassInfo()
{
    QUrl url("http://127.0.0.1:8080/api/teacher/myclass/" + m_teacher.Tno);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    //连接信号槽
    connect(manager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(getClassInfoReply(QNetworkReply *)));
    QNetworkRequest request = JsonTools::getJsonHeader(m_teacher.Token, url);
    manager->get(request);// 发送请求
}

//获取个人课堂信息响应槽函数
void teacherHome::getClassInfoReply(QNetworkReply *reply)
{
    qDebug()<<"获取个人课堂信息响应槽函数"<<endl;
    QJsonValue jsonData = JsonTools::getDataOfGet(reply);
    if (jsonData.isNull())
    {
        QMessageBox::warning(this,"result:","jsonData为空");
        return ;
    }
    showTableInfo(jsonData);
}

//表格显示信息
void teacherHome::showTableInfo(QJsonValue jsonValue, int show_type)
{
    qDebug()<<"表格显示信息"<<endl;
    QStringList classInfo;
    QJsonArray array = jsonValue.toArray();
    if (show_type == 0)
    {
        for(int i=0;i<array.size(); i++)
        {
            classInfo.clear();
           QJsonValue iconArray = array.at(i);
           QJsonObject icon = iconArray.toObject();
           classInfo<<icon["Cnumber"].toString();
           classInfo<<icon["Cname"].toString();
           classInfo<<QString("%1").arg(icon["Ccredit"].toDouble());
           classInfo<<QString::number(icon["Chour"].toInt());
           classInfo<<icon["Ctype"].toString();
           classInfo<<icon["Cdept"].toString();
           classInfo<<icon["Ctime"].toString();
           classInfo<<icon["Csession"].toString();
           classInfo<<icon["Caddress"].toString();
           classInfo<<QString::number(icon["Csum"].toInt());
           for(int k=0;k<classInfo.size(); k++)qDebug()<<classInfo.at(k)<<" ";
           qDebug()<<endl;


           int row=ui->tableWidget->rowCount();
           ui->tableWidget->setRowCount(row+1);  //表格加一行
           for(int j=0;j<10;j++)
           {
               QTableWidgetItem *newItem =new QTableWidgetItem(classInfo.at(j));
               ui->tableWidget->setItem(i,j,newItem);
           }
           QPushButton *pushbutton = new QPushButton;
           ui->tableWidget->setCellWidget(i,10,pushbutton);
           pushbutton->setText("查看学生");
           connect(pushbutton,SIGNAL(clicked()), this, SLOT(queryStudentOfClass()));
           QPushButton *pushbutton1 = new QPushButton;
           ui->tableWidget->setCellWidget(i,11,pushbutton1);
           pushbutton1->setText("修改");
           connect(pushbutton1,SIGNAL(clicked()), this, SLOT(modifyClassInfo()));
        }
    }
    else if (show_type == 1)
    {
        ui->studentTable->clearContents();
        ui->studentTable->setRowCount(0);
        for(int i=0;i<array.size(); i++)
        {
           classInfo.clear();
           QJsonValue iconArray = array.at(i);
           QJsonObject icon = iconArray.toObject();
           classInfo<<icon["Cnumber"].toString();
           classInfo<<icon["Sno"].toString();
           classInfo<<icon["Sname"].toString();
           classInfo<<icon["Smajor"].toString();
           classInfo<<icon["Ssex"].toString();
           classInfo<<icon["Sclass"].toString();
           for(int k=0;k<classInfo.size(); k++)qDebug()<<classInfo.at(k)<<" ";
           qDebug()<<endl;

           int row=ui->studentTable->rowCount();
           ui->studentTable->setRowCount(row+1);  //表格加一行
           for(int j=0;j<6;j++)
           {
               QTableWidgetItem *newItem =new QTableWidgetItem(classInfo.at(j));
               ui->studentTable->setItem(i,j,newItem);
           }
        }
    }
}

//修改课堂信息
void teacherHome::modifyClassInfo()
{
    qDebug()<<"修改课堂信息"<<endl;
    QPushButton *button = dynamic_cast<QPushButton *>(QObject::sender());
    QModelIndex index = ui->tableWidget->indexAt(button->pos());
    int row = index.row();
    int col = index.column();
    QStringList classInfo;
    for (int i =0 ; i < col-1; i++ )
    {   // 课堂编号 课堂名称 学时 学分 课程类型 开课院系 上课日期 课堂节次 上课地点 课堂人数
        classInfo<<ui->tableWidget->item(row, i)->text();
    }

    ModifyClassInfo *modifyClass = new ModifyClassInfo(1, classInfo, m_teacher.Token, m_teacher.Tno);
    modifyClass->show();
//    delete modifyClass;
//    this->show();
}

//获取个人信息
void teacherHome::getPersonalInfo()
{
    QUrl url("http://127.0.0.1:8080/api/teacher/" + m_teacher.Tno);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // 连接信号槽
    connect(manager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(personalInfoReply(QNetworkReply *)));
    QNetworkRequest request = JsonTools::getJsonHeader(m_teacher.Token, url);
    manager->get(request);// 发送请求
}

//获取个人信息槽函数
void teacherHome::personalInfoReply(QNetworkReply *reply)
{
    QJsonValue jsonData = JsonTools::getDataOfGet(reply);
    if (jsonData.isNull())
    {
        QMessageBox::warning(this,"result:","json data  为空");
    }
    QJsonObject obj;

    if (!jsonData.isObject())
    {
        QMessageBox::warning(this,"result:","json非Object");
        return;
    }

    //显示个人信息
    obj = jsonData.toObject();
    if (obj.contains("Tname"))
    {
        m_teacher.Tname = obj.take("Tname").toString();
        ui->nameEdit->setText(m_teacher.Tname);
    }
    if (obj.contains("Tsex"))
    {
        if (obj.value("Tsex").toString().contains("男"))ui->sexBox->setCurrentIndex(0);
        if (obj.value("Tsex").toString().contains("女"))ui->sexBox->setCurrentIndex(1);
        m_teacher.Tsex = ui->sexBox->currentText();
    }
    if (obj.contains("Tbirthday"))
    {
        m_teacher.Tbirthday = obj.value("Tbirthday").toString();
        ui->birthdayEdit->setText(m_teacher.Tbirthday);
    }
    if (obj.contains("Tclass"))
    {
        m_teacher.Tclass = obj.value("Tclass").toString();
        ui->classEdit->setText(m_teacher.Tclass);
    }
    if (obj.contains("Tno"))
    {
        m_teacher.Tno = obj.value("Tno").toString();
        ui->userIDEdit->setText(m_teacher.Tno);
    }
    if (obj.contains("Tdept"))
    {
        m_teacher.Tmajor = obj.value("Tdept").toString();
        ui->majorEdit->setText(m_teacher.Tmajor);
    }
    if (obj.contains("Tphone"))
    {
        m_teacher.Tphone = obj.value("Tphone").toString();
        ui->phoneEdit->setText(m_teacher.Tphone);
    }

}


