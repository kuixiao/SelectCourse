#include "deanhome.h"
#include "ui_deanhome.h"

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
#include "course.h"
#include "classdata.h"
#include "register.h"
#include "modifypersonalinfo.h"


extern int identity;
QStringList itemInfo;
QStringList TnoList,TnameList;
QStringList CnoList,CnameList;

DeanHome::DeanHome(QString userID,QString token,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeanHome)
{
    ui->setupUi(this);

    m_dean.Identity = identity;
    m_dean.Dno = userID;
    m_dean.Token = token;

    initTable();
    getCourseInfo();
    getPersonalInfo();
    getTeacherInfo();
    ui->tabWidget->setCurrentIndex(1);

    setSlots();
}

DeanHome::~DeanHome()
{
    delete ui;
}

void DeanHome::setSlots()
{
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabSwich(int)));
    connect(ui->modifyBtn, SIGNAL(clicked()), this, SLOT(modifyDean()));
    connect(ui->modifyPwdBtn, SIGNAL(clicked()), this, SLOT(modifyPwdDean()));

    connect(ui->courseTable, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(selectItem(int, int)));
    connect(ui->classTable, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(selectItem(int, int)));
    connect(ui->teacherTable, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(selectItem(int, int)));
    connect(ui->studentTable, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(selectItem(int, int)));

    connect(ui->addCourseBtn, SIGNAL(clicked()), this, SLOT(addCourse()));
    connect(ui->addClassBtn, SIGNAL(clicked()), this, SLOT(addClass()));
    connect(ui->addTeacherBtn, SIGNAL(clicked()), this, SLOT(addTeacher()));
    connect(ui->addStudentBtn, SIGNAL(clicked()), this, SLOT(addStudent()));

    connect(ui->modifyCourseBtn, SIGNAL(clicked()), this, SLOT(modifyCourse()));
    connect(ui->modifyClassBtn, SIGNAL(clicked()), this, SLOT(modifyClass()));
    connect(ui->modifyTeacherBtn, SIGNAL(clicked()), this, SLOT(modifyTeacher()));
    connect(ui->modifyStudentBtn, SIGNAL(clicked()), this, SLOT(modifyStudent()));

    connect(ui->deleteCourseBtn, SIGNAL(clicked()), this, SLOT(deleteCourse()));
    connect(ui->deleteClassBtn, SIGNAL(clicked()), this, SLOT(deleteClass()));
    connect(ui->deleteTeacherBtn, SIGNAL(clicked()), this, SLOT(deleteTeacher()));
    connect(ui->deleteStudentBtn, SIGNAL(clicked()), this, SLOT(deleteStudent()));

    //connect(ui->modifyBtn,SIGNAL(clicked()), this, SLOT(modifyUserInfo()));
    //connect(ui->modifyPwdBtn, SIGNAL(clicked()), this, SLOT(modifyPassword()));
}

//系主任修改个人信息按钮槽函数
void DeanHome::modifyDean()
{
    ModifyPersonalInfo *modify = new ModifyPersonalInfo(2,m_dean);
    modify->show();
}

//系主任修改密码按钮槽函数
void DeanHome::modifyPwdDean()
{
    ModifyPassword *modifyPwd = new ModifyPassword(m_dean.Token,m_dean.Dno);
    modifyPwd->show();
}

//添加课程按钮槽函数
void DeanHome::addCourse()
{
    Course *course = new Course(m_dean.Token, m_dean.Dno, 0);
    course->show();
}

//修改课程按钮槽函数
void DeanHome::modifyCourse()
{
    if (ui->CourseLineEdit->text().isEmpty())
    {
        QMessageBox::information(this, "提示:", "请选择需要进行修改的课程信息");
        return;
    }
    itemInfo.clear();
    for (int i = 0; i < 6; i++)
    {
        itemInfo<<ui->courseTable->item(m_row, i)->text();
    }
    Course *course = new Course(m_dean.Token, m_dean.Dno, 1);
    course->show();
}

//删除课程按钮槽函数
void DeanHome::deleteCourse()
{
    QString courseID = ui->CourseLineEdit->text();
    if (courseID.isEmpty())
    {
        QMessageBox::information(this, "提示:", "请选择需要进行修改的课程信息");
        return;
    }
    QUrl url("http://127.0.0.1:8080/api/dean/delete/course/"
             + m_dean.Dno + "/" + courseID);
    QNetworkRequest request = JsonTools::getJsonHeader(m_dean.Token,url);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    // 发送请求
    manager->deleteResource(request);
}

//添加课堂按钮槽函数
void DeanHome::addClass()
{
    CnoList.clear();
    CnameList.clear();
    TnoList.clear();
    TnameList.clear();
    int courseSum = ui->courseTable->rowCount();
    int teacherSum = ui->teacherTable->rowCount();
    qDebug()<<"courseSum "<<courseSum<<"teacherSum "<<teacherSum<<endl;
    for (int i = 0; i < courseSum; i++)
    {
        CnoList<<ui->courseTable->item(i,0)->text();
        CnameList<<ui->courseTable->item(i,1)->text();
        qDebug()<<CnoList.at(i)<<" "<<CnameList.at(i)<<endl;
    }
    for (int i = 0; i < teacherSum; i++)
    {
        TnoList<<ui->teacherTable->item(i,0)->text();
        TnameList<<ui->teacherTable->item(i,1)->text();
        qDebug()<<TnoList.at(i)<<" "<<TnameList.at(i)<<endl;
    }

    ClassData *classData = new ClassData(m_dean.Token, m_dean.Dno, 0,
               TnoList, TnameList,CnoList, CnameList,itemInfo);
    classData->show();
}

//修改课堂按钮槽函数
void DeanHome::modifyClass()
{
    if (ui->ClassLineEdit->text().isEmpty())
    {
        QMessageBox::information(this, "提示:", "请选择需要进行修改的课程信息");
        return;
    }
    itemInfo.clear();
    CnoList.clear();
    CnameList.clear();
    TnoList.clear();
    TnameList.clear();
    int teacherSum = ui->teacherTable->rowCount();
    qDebug()<<"teacherSum"<<teacherSum<<endl;
    for (int i = 0; i < 8; i++)
    {
        itemInfo<<ui->classTable->item(m_row, i)->text();
    }
    for (int i = 0; i < teacherSum; i++)
    {
        TnoList<<ui->teacherTable->item(i,0)->text();
        TnameList<<ui->teacherTable->item(i,1)->text();
    }

    ClassData *classData = new ClassData(m_dean.Token, m_dean.Dno, 1,
               TnoList, TnameList,CnoList,CnameList,itemInfo);
    classData->show();
}

//删除课堂按钮槽函数
void DeanHome::deleteClass()
{
    QString ClassID = ui->ClassLineEdit->text();
    if (ClassID.isEmpty())
    {
        QMessageBox::information(this, "提示:", "请选择需要进行修改的课程信息");
        return;
    }
    QUrl url("http://127.0.0.1:8080/api/dean/delete/class/"
             + m_dean.Dno + "/" + ClassID);
    QNetworkRequest request = JsonTools::getJsonHeader(m_dean.Token,url);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    // 发送请求
    manager->deleteResource(request);
}

//添加老师按钮槽函数
void DeanHome::addTeacher()
{
    Register *stuReg = new Register(1);
    stuReg->show();
}

//修改老师按钮槽函数
void DeanHome::modifyTeacher()
{
    if (ui->teacherLineEdit->text().isEmpty())
    {
        QMessageBox::information(this, "提示:", "请选择需要进行修改的老师信息");
        return;
    }
    teacherInfo teacher;
    teacher.Token = m_dean.Token;
    teacher.Tno = ui->teacherTable->item(m_row, 0)->text();
    teacher.Tname = ui->teacherTable->item(m_row, 1)->text();
    teacher.Tsex = ui->teacherTable->item(m_row, 2)->text();
    teacher.Tbirthday = ui->teacherTable->item(m_row, 3)->text();
    teacher.Tmajor = ui->teacherTable->item(m_row, 4)->text();
    teacher.Tphone = ui->teacherTable->item(m_row, 5)->text();
    teacher.Tclass = ui->teacherTable->item(m_row, 6)->text();
    ModifyPersonalInfo *modify = new ModifyPersonalInfo(4,teacher);
    modify->show();
}

//删除教师按钮槽函数
void DeanHome::deleteTeacher()
{
    QString TeacherID = ui->teacherLineEdit->text();
    if (TeacherID.isEmpty())
    {
        QMessageBox::information(this, "提示:", "请选择需要进行修改的课程信息");
        return;
    }
    QUrl url("http://127.0.0.1:8080/api/dean/delete/teacher/"
             + m_dean.Dno + "/" + TeacherID);
    QNetworkRequest request = JsonTools::getJsonHeader(m_dean.Token,url);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    // 发送请求
    manager->deleteResource(request);
}

//添加学生按钮槽函数
void DeanHome::addStudent()
{
    Register *stuReg = new Register(0);
    stuReg->show();
}

//修改学生按钮槽函数
void DeanHome::modifyStudent()
{
    if (ui->StudentLineEdit->text().isEmpty())
    {
        QMessageBox::information(this, "提示:", "请选择需要进行修改的学生信息");
        return;
    }
    studentInfo student;
    student.Sno = ui->studentTable->item(m_row, 0)->text();
    student.Smajor = ui->studentTable->item(m_row, 1)->text();
    student.Sname = ui->studentTable->item(m_row, 2)->text();
    student.Ssex = ui->studentTable->item(m_row, 3)->text();
    student.Sbirthday = ui->studentTable->item(m_row, 4)->text();
    student.Sclass = ui->studentTable->item(m_row, 5)->text();
    student.Sphone = ui->studentTable->item(m_row, 6)->text();
    student.Token = m_dean.Token;
    ModifyPersonalInfo *modify = new ModifyPersonalInfo(3,student);
    modify->show();
}

//删除学生按钮槽函数
void DeanHome::deleteStudent()
{
    QString StudentID = ui->StudentLineEdit->text();
    if (StudentID.isEmpty())
    {
        QMessageBox::information(this, "提示:", "请选择需要进行修改的课程信息");
        return;
    }
    QUrl url("http://127.0.0.1:8080/api/dean/delete/student/"
             + m_dean.Dno + "/" + StudentID);
    QNetworkRequest request = JsonTools::getJsonHeader(m_dean.Token,url);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    // 发送请求
    manager->deleteResource(request);
}

//解析响应Json数据
void DeanHome::replyFinished(QNetworkReply *reply)
{
    JsonTools::replyFinished(reply);
}

//选项卡切换槽函数
void DeanHome::tabSwich(int index)
{
    if (index == 0) //个人信息
    {
        getPersonalInfo();
    }
    else if (index == 1)    //课程信息管理
    {
        ui->courseTable->clearContents();
        ui->courseTable->setRowCount(0);
        getCourseInfo();
    }
    else if (index == 2)    //课堂信息管理
    {
        ui->classTable->clearContents();
        ui->classTable->setRowCount(0);
        getClassInfo();
    }
    else if (index == 3)    //教师信息管理
    {
        ui->teacherTable->clearContents();
        ui->teacherTable->setRowCount(0);
        getTeacherInfo();
    }
    else if (index == 4)    //学生信息管理
    {
        ui->studentTable->clearContents();
        ui->studentTable->setRowCount(0);
        getStudentInfo();
    }
    else if (index == 5)    //信息查询
    {

    }
}

//双击表格槽函数
void DeanHome::selectItem(int row, int colum)
{
    m_row = row;
    m_colum = colum;
    int tabIndex = ui->tabWidget->currentIndex();
    if (tabIndex == 1)
    {
        ui->CourseLineEdit->setText(ui->courseTable->item(row, 0)->text());
    }
    else if (tabIndex == 2)
    {
        ui->ClassLineEdit->setText(ui->classTable->item(row, 0)->text());
    }
    else if (tabIndex == 3)
    {
        ui->teacherLineEdit->setText(ui->teacherTable->item(row, 0)->text());
    }
    else if (tabIndex == 4)
    {
        ui->StudentLineEdit->setText(ui->studentTable->item(row, 0)->text());
    }
}

//选项卡切换获取课程信息
void DeanHome::getCourseInfo()
{
    QUrl url("http://127.0.0.1:8080/api/dean/allcourse/" + m_dean.Dno);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // 连接信号槽
    connect(manager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(getCourseInfoReply(QNetworkReply *)));
    QNetworkRequest request = JsonTools::getJsonHeader( m_dean.Token, url);
    manager->get(request);// 发送请求
}

//选项卡切换获取课堂信息
void DeanHome::getClassInfo()
{
    QUrl url("http://127.0.0.1:8080/api/dean/allclass/" + m_dean.Dno);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // 连接信号槽
    connect(manager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(getClassInfoReply(QNetworkReply *)));
    QNetworkRequest request = JsonTools::getJsonHeader( m_dean.Token, url);
    manager->get(request);// 发送请求
}

//选项卡切换获取教师信息
void DeanHome::getTeacherInfo()
{
    QUrl url("http://127.0.0.1:8080/api/dean/allteacher/" + m_dean.Dno);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // 连接信号槽
    connect(manager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(getTeacherInfoReply(QNetworkReply *)));
    QNetworkRequest request = JsonTools::getJsonHeader( m_dean.Token, url);
    manager->get(request);// 发送请求
}

//选项卡切换获取学生信息
void DeanHome::getStudentInfo()
{
    QUrl url("http://127.0.0.1:8080/api/dean/allstudent/" + m_dean.Dno);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // 连接信号槽
    connect(manager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(getStudentInfoReply(QNetworkReply *)));
    QNetworkRequest request = JsonTools::getJsonHeader( m_dean.Token, url);
    manager->get(request);// 发送请求
}

//获取课程信息Json响应槽函数
void DeanHome::getCourseInfoReply(QNetworkReply *reply)
{
    qDebug()<<"获取课程信息Json响应槽函数"<<endl;
    QJsonValue jsonData = JsonTools::getDataOfGet(reply);
    if (jsonData.isNull())
    {
        QMessageBox::warning(this,"result:","jsonData为空");
        return ;
    }
    showCourseInfo(jsonData);
}

//获取课堂信息Json响应槽函数
void DeanHome::getClassInfoReply(QNetworkReply *reply)
{
    qDebug()<<"获取课堂信息Json响应槽函数"<<endl;
    QJsonValue jsonData = JsonTools::getDataOfGet(reply);
    if (jsonData.isNull())
    {
        QMessageBox::warning(this,"result:","jsonData为空");
        return ;
    }
    showClassInfo(jsonData);
}

//获取教师信息Json响应槽函数
void DeanHome::getTeacherInfoReply(QNetworkReply *reply)
{
    qDebug()<<"获取教师信息Json响应槽函数"<<endl;
    QJsonValue jsonData = JsonTools::getDataOfGet(reply);
    if (jsonData.isNull())
    {
        QMessageBox::warning(this,"result:","jsonData为空");
        return ;
    }
    showTeacherInfo(jsonData);
}

//获取学生信息Json响应槽函数
void DeanHome::getStudentInfoReply(QNetworkReply *reply)
{
    qDebug()<<"获取学生信息Json响应槽函数"<<endl;
    QJsonValue jsonData = JsonTools::getDataOfGet(reply);
    if (jsonData.isNull())
    {
        QMessageBox::warning(this,"result:","jsonData为空");
        return ;
    }
    showStudentInfo(jsonData);
}

//设置表格属性
void DeanHome::initTable(QTableWidget *table,QStringList headers, int cloum)
{
    table->setRowCount(0);
    table->setColumnCount(cloum);
    table->setHorizontalHeaderLabels(headers);
    //表格属性设置
    table->verticalHeader()->hide();
    table->horizontalHeader()->setSectionsClickable(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列宽自适应
    table->setFrameShape(QFrame::NoFrame);
}

//设置表格属性
void DeanHome::initTable()
{
    //课程信息表
    //课程代码 课程名称 学分 学时 课程类型 开课院系
    QStringList courseheaders;
    courseheaders<<"课程代码"<<"课程名称"<<"学分"<<"学时"<<"课程类型"<<"开课院系";
    initTable(ui->courseTable, courseheaders, 6);

    //课堂信息表
    QStringList classheaders;
    classheaders<<"课程代码"<<"课堂编号"<<"课程名称"<<"上课日期"<<"课堂节次"<<"上课地点"<<"课堂人数"<<"任课教师";
    initTable(ui->classTable, classheaders, 8);

    //教师信息表
    QStringList teacherheaders;
    teacherheaders<<"教师职工编号"<<"教师姓名"<<"性别"<<"教师出生日期"<<"教师所属院系"<<"教师联系电话"<<"教师职称信息";
    initTable(ui->teacherTable, teacherheaders, 7);

    //学生信息表
    QStringList studentheaders;
    studentheaders<<"学号"<<"专业"<<"姓名"<<"性别"<<"出生日期"<<"班级"<<"联系方式";
    initTable(ui->studentTable, studentheaders, 7);
}

//获取个人信息
void DeanHome::getPersonalInfo()
{
    QUrl url("http://127.0.0.1:8080/api/dean/" + m_dean.Dno);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // 连接信号槽
    connect(manager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(personalInfoReply(QNetworkReply *)));
    QNetworkRequest request = JsonTools::getJsonHeader( m_dean.Token, url);
    manager->get(request);// 发送请求
}

//获取个人信息槽函数
void DeanHome::personalInfoReply(QNetworkReply *reply)
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
    if (obj.contains("Dname"))
    {
         m_dean.Dname = obj.take("Dname").toString();
        ui->DnameEdit->setText( m_dean.Dname);
    }
    if (obj.contains("Dsex"))
    {
        if (obj.value("Dsex").toString().contains("男"))ui->DsexBox->setCurrentIndex(0);
        if (obj.value("Dsex").toString().contains("女"))ui->DsexBox->setCurrentIndex(1);
         m_dean.Dsex = ui->DsexBox->currentText();
    }
    if (obj.contains("Dbirthday"))
    {
         m_dean.Dbirthday = obj.value("Dbirthday").toString();
        ui->DbirthdayEdit->setText( m_dean.Dbirthday);
    }
    if (obj.contains("Dclass"))
    {
         m_dean.Dclass = obj.value("Dclass").toString();
        ui->DclassEdit->setText( m_dean.Dclass);
    }
    if (obj.contains("Dno"))
    {
         m_dean.Dno = obj.value("Dno").toString();
        ui->DnoEdit->setText( m_dean.Dno);
    }
    if (obj.contains("Ddept"))
    {
         m_dean.Dmajor = obj.value("Ddept").toString();
        ui->DdeptEdit->setText( m_dean.Dmajor);
    }
    if (obj.contains("Dphone"))
    {
        m_dean.Dphone = obj.value("Dphone").toString();
        ui->DphoneEdit->setText( m_dean.Dphone);
    }
    if (obj.contains("Dpassword"))
    {
        m_dean.Dpassword = obj.value("Dpassword").toString();
    }
}

//表格显示信息
void DeanHome::showCourseInfo(QJsonValue jsonValue)
{
    qDebug()<<"表格显示信息"<<endl;
    QJsonArray array = jsonValue.toArray();
    for(int i=0;i<array.size(); i++)
    {
       QStringList Info;
       QJsonValue iconArray = array.at(i);
       QJsonObject icon = iconArray.toObject();
       Info<<icon["Cno"].toString();
       Info<<icon["Cname"].toString();
       Info<<QString("%1").arg(icon["Ccredit"].toDouble());
       Info<<QString::number(icon["Chour"].toInt());
       Info<<icon["Ctype"].toString();
       Info<<icon["Cdept"].toString();
       int row=ui->courseTable->rowCount();
       ui->courseTable->setRowCount(row+1);  //表格加一行
       for(int j=0;j<Info.size();j++)
       {   qDebug()<<Info.at(j)<<" ";
           QTableWidgetItem *newItem =new QTableWidgetItem(Info.at(j));
           ui->courseTable->setItem(i,j,newItem);
       }
       qDebug()<<endl;
   }
}
void DeanHome::showClassInfo(QJsonValue jsonValue)
{
    qDebug()<<"表格显示信息"<<endl;
    QJsonArray array = jsonValue.toArray();

    for(int i=0;i<array.size(); i++)
    {
       QStringList Info;
       QJsonValue iconArray = array.at(i);
       QJsonObject icon = iconArray.toObject();
       Info<<icon["Cno"].toString();
       Info<<icon["Cnumber"].toString();
       Info<<icon["Cname"].toString();
       Info<<icon["Ctime"].toString();
       Info<<icon["Csession"].toString();
       Info<<icon["Caddress"].toString();
       Info<<QString::number(icon["Csum"].toInt());
       Info<<icon["Tname"].toString();

       int row=ui->classTable->rowCount();
       ui->classTable->setRowCount(row+1);  //表格加一行
       for(int j=0;j<Info.size();j++)
       {   qDebug()<<Info.at(j)<<" ";
           QTableWidgetItem *newItem =new QTableWidgetItem(Info.at(j));
           ui->classTable->setItem(i,j,newItem);
       }
       qDebug()<<endl;
   }
}
void DeanHome::showTeacherInfo(QJsonValue jsonValue)
{
    qDebug()<<"表格显示信息"<<endl;
    QJsonArray array = jsonValue.toArray();

    for(int i=0;i<array.size(); i++)
    {
       QStringList Info;
       QJsonValue iconArray = array.at(i);
       QJsonObject icon = iconArray.toObject();
       Info<<icon["Tno"].toString();
       Info<<icon["Tname"].toString();
       Info<<icon["Tsex"].toString();
       Info<<icon["Tbirthday"].toString();
       Info<<icon["Tdept"].toString();
       Info<<icon["Tphone"].toString();
       Info<<icon["Tclass"].toString();

       int row=ui->teacherTable->rowCount();
       ui->teacherTable->setRowCount(row+1);  //表格加一行
       for(int j=0;j<Info.size();j++)
       {   qDebug()<<Info.at(j)<<" ";
           QTableWidgetItem *newItem =new QTableWidgetItem(Info.at(j));
           ui->teacherTable->setItem(i,j,newItem);
       }
       qDebug()<<endl;
   }
}
void DeanHome::showStudentInfo(QJsonValue jsonValue)
{
    qDebug()<<"表格显示信息"<<endl;
    QJsonArray array = jsonValue.toArray();
    for(int i=0;i<array.size(); i++)
    {
       QStringList Info;
       QJsonValue iconArray = array.at(i);
       QJsonObject icon = iconArray.toObject();
       Info<<icon["Sno"].toString();
       Info<<icon["Smajor"].toString();
       Info<<icon["Sname"].toString();
       Info<<icon["Ssex"].toString();
       Info<<icon["Sbirthday"].toString();
       Info<<icon["Sclass"].toString();
       Info<<icon["Sphone"].toString();

       int row=ui->studentTable->rowCount();
       ui->studentTable->setRowCount(row+1);  //表格加一行
       for(int j=0;j<Info.size();j++)
       {   qDebug()<<Info.at(j)<<" ";
           QTableWidgetItem *newItem =new QTableWidgetItem(Info.at(j));
           ui->studentTable->setItem(i,j,newItem);
       }
       qDebug()<<endl;
   }
}
