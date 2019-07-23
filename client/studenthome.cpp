#include "studenthome.h"
#include "ui_studenthome.h"
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
#include "modifypassword.h"
#include "jsontools.h"

extern QString Token;
extern int identity;

StudentHome::StudentHome(QString userID, QString token, QDialog *parent) :
    QDialog(parent), ui(new Ui::StudentHome)
{
    ui->setupUi(this);
    m_student.Identity = identity;
    m_student.Sno = userID;
    m_student.Token = token;
    ui->tabWidget->setTabText(0,"个人信息");
    ui->tabWidget->setTabText(1,"选课");
    ui->tabWidget->setTabText(2,"查看已选课程");
    ui->tabWidget->setTabPosition(QTabWidget::West);
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle(100, 100));

    //选课课堂信息表
    QStringList headers;
    headers<<"课堂编号"<<"课程名称"<<"学分"<<"学时"<<"上课日期"<<"课堂节次"<<"上课地点"<<"教师姓名"<<" ";
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    //表格属性设置
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->setSectionsClickable(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列宽自适应
    ui->tableWidget->setFrameShape(QFrame::NoFrame);

    headers<<"课堂编号"<<"课程名称"<<"学分"<<"学时"<<"上课日期"<<"课堂节次"<<"上课地点"<<"教师姓名"<<" ";
    ui->classInfoTable->setRowCount(0);
    ui->classInfoTable->setColumnCount(9);
    ui->classInfoTable->setHorizontalHeaderLabels(headers);
    //表格属性设置
    ui->classInfoTable->verticalHeader()->hide();
    ui->classInfoTable->horizontalHeader()->setSectionsClickable(false);
    ui->classInfoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列宽自适应
    ui->classInfoTable->setFrameShape(QFrame::NoFrame);

    getPersonalInfo();  //获取个人信息
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(getInfo(int)));
    connect(ui->modifyBtn,SIGNAL(clicked()), this, SLOT(modifyUserInfo()));
    connect(ui->modifyPwdBtn, SIGNAL(clicked()), this, SLOT(modifyPassword()));
}

StudentHome::~StudentHome()
{
    delete ui;
}

//修改密码按钮槽函数
void StudentHome::modifyPassword()
{
    ModifyPassword *modifyPwd = new ModifyPassword(m_student.Token,m_student.Sno);
    modifyPwd->show();
}

//修改个人信息按钮槽函数
void StudentHome::modifyUserInfo()
{
    qDebug()<<"修改个人信息按钮槽函数"<<endl;
    ModifyPersonalInfo *modifyPersonalInfo = new ModifyPersonalInfo(identity, m_student);
    modifyPersonalInfo->show();
}

//选课按钮槽函数
void StudentHome::selectCourse()
{
    QPushButton *button = dynamic_cast<QPushButton *>(QObject::sender());
    QModelIndex index = ui->tableWidget->indexAt(button->pos());
    int row = index.row();
    int col = index.column();
    qDebug()<<row<<" "<<col<<endl;
    QUrl url("http://127.0.0.1:8080/api/student/add/stucourse/" + m_student.Sno);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QJsonObject json;
    json.insert("Cnumber", ui->tableWidget->item(row, 0)->text());
    json.insert("Sno", m_student.Sno);
    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);
    // 连接信号槽
    connect(manager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(replyFinished(QNetworkReply *)));
    QNetworkRequest request = JsonTools::getJsonHeader(m_student.Token, url);
    manager->post(request,dataArray);// 发送请求
}

//选课响应槽函数
void StudentHome::replyFinished(QNetworkReply *reply)
{
    JsonTools::replyFinished(reply);
}

//退选按钮槽函数
void StudentHome::withdrawal()
{
    QPushButton *button = dynamic_cast<QPushButton *>(QObject::sender());
    QModelIndex index = ui->tableWidget->indexAt(button->pos());
    int row = index.row();
    int col = index.column();
    qDebug()<<row<<" "<<col<<endl;
}

//选项卡切换槽函数
void StudentHome::getInfo(int index)
{
    if (index == 0) //个人信息
    {
        getPersonalInfo();
    }
    else if (index == 1)    //选课
    {
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);
        getCourseInfo();
    }
    else if (index == 2)  //选课结果
    {
        ui->classInfoTable->clearContents();
        ui->classInfoTable->setRowCount(0);
        getPersonalClass();
    }
}

//获取选课课堂信息
void StudentHome::getCourseInfo()
{
    QUrl url("http://127.0.0.1:8080/api/student/allclass/" + m_student.Sno);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    //连接信号槽
    connect(manager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(getCourseInfoReply(QNetworkReply *)));
    QNetworkRequest request = JsonTools::getJsonHeader(m_student.Token, url);
    manager->get(request);// 发送请求
}

//获取选课课堂信息槽函数
void StudentHome::getCourseInfoReply(QNetworkReply *reply)
{
    qDebug()<<"获取选课课堂信息槽函数"<<endl;
    QJsonValue jsonData = JsonTools::getDataOfGet(reply);
    if (jsonData.isNull())
    {
        QMessageBox::warning(this,"result:","jsonData为空");
        return ;
    }
    showTableInfo(jsonData, 0);
}

//表格显示信息
void StudentHome::showTableInfo(QJsonValue jsonValue, int show_type)
{
    qDebug()<<"表格显示信息"<<endl;
    QStringList classInfo;
    QJsonArray array = jsonValue.toArray();
    for(int i=0;i<array.size(); i++)
    {
       classInfo.clear();
       QJsonValue iconArray = array.at(i);
       QJsonObject icon = iconArray.toObject();
       classInfo<<icon["Cnumber"].toString();
       classInfo<<icon["Cname"].toString();
       classInfo<<QString("%1").arg(icon["Ccredit"].toDouble());
       classInfo<<QString::number(icon["Chour"].toInt());
       classInfo<<icon["Ctime"].toString();
       classInfo<<icon["Csession"].toString();
       classInfo<<icon["Caddress"].toString();
       classInfo<<icon["Tname"].toString();
       for(int k=0;k<classInfo.size(); k++)qDebug()<<classInfo.at(k)<<" ";
       qDebug()<<endl;

       QPushButton *pushbutton = new QPushButton;
       if (show_type == 0)
       {
           int row=ui->tableWidget->rowCount();
           ui->tableWidget->setRowCount(row+1);  //表格加一行
           for(int j=0;j<8;j++)
           {
               QTableWidgetItem *newItem =new QTableWidgetItem(classInfo.at(j));
               ui->tableWidget->setItem(i,j,newItem);
           }
           ui->tableWidget->setCellWidget(i,8,pushbutton);
           pushbutton->setText("选课");
           connect(pushbutton,SIGNAL(clicked()), this, SLOT(selectCourse()));
       }
       else if (show_type == 1)
       {
           int row=ui->classInfoTable->rowCount();
           ui->classInfoTable->setRowCount(row+1);  //表格加一行
           for(int j=0;j<8;j++)
           {
               QTableWidgetItem *newItem =new QTableWidgetItem(classInfo.at(j));
               ui->classInfoTable->setItem(i,j,newItem);
           }
           ui->classInfoTable->setCellWidget(i,8,pushbutton);
           pushbutton->setText("退选");
           connect(pushbutton,SIGNAL(clicked()), this, SLOT(withdrawal()));
       }
    }
}

//获取个人选课结果信息
void StudentHome::getPersonalClass()
{
    qDebug()<<"获取个人选课结果信息"<<endl;
    QUrl url("http://127.0.0.1:8080/api/student/myclass/" + m_student.Sno);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // 连接信号槽
    connect(manager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(getPersonalClassInfoReply(QNetworkReply *)));
    QNetworkRequest request = JsonTools::getJsonHeader(m_student.Token, url);
    manager->get(request);// 发送请求
}

//获取个人选课结果信息槽函数
void StudentHome::getPersonalClassInfoReply(QNetworkReply *reply)
{
    qDebug()<<"获取个人选课结果信息槽函数"<<endl;
    QJsonValue jsonData = JsonTools::getDataOfGet(reply);
    if (jsonData.isNull())
    {
        QMessageBox::warning(this,"result:","jsonData为空");
        return ;
    }
    showTableInfo(jsonData, 1);
}

//获取个人信息
void StudentHome::getPersonalInfo()
{
    QUrl url("http://127.0.0.1:8080/api/student/" + m_student.Sno);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // 连接信号槽
    connect(manager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(personalInfoReply(QNetworkReply *)));

    QNetworkRequest request = JsonTools::getJsonHeader(m_student.Token, url);
    manager->get(request);// 发送请求
}

//获取个人信息槽函数
void StudentHome::personalInfoReply(QNetworkReply *reply)
{
    QJsonValue jsonData = JsonTools::getDataOfGet(reply);
    if (jsonData.isNull())
    {
        QMessageBox::warning(this,"result:","json data  为空");
    }
    QJsonObject obj;
    if (jsonData.isObject())
    {
        obj = jsonData.toObject();
        showTableInfo(obj, 0);
    }
    else
    {
        QMessageBox::warning(this,"result:","json非Object");
    }

    if (jsonData.isObject())
    {   //显示个人信息
        obj = jsonData.toObject();
        if (obj.contains("Sname"))
        {
            m_student.Sname = obj.take("Sname").toString();
            ui->nameEdit->setText(m_student.Sname);
        }
        if (obj.contains("Ssex"))
        {
            if (obj.value("Ssex").toString().contains("男"))ui->sexBox->setCurrentIndex(0);
            if (obj.value("Ssex").toString().contains("女"))ui->sexBox->setCurrentIndex(1);
            m_student.Ssex = ui->sexBox->currentText();
        }
        if (obj.contains("Sbirthday"))
        {
            m_student.Sbirthday = obj.value("Sbirthday").toString();
            ui->birthdayEdit->setText(m_student.Sbirthday);
        }
        if (obj.contains("Sclass"))
        {
            m_student.Sclass = obj.value("Sclass").toString();
            ui->classEdit->setText(m_student.Sclass);
        }
        if (obj.contains("Sno"))
        {
            m_student.Sno = obj.value("Sno").toString();
            ui->userIDEdit->setText(m_student.Sno);
        }
        if (obj.contains("Smajor"))
        {
            m_student.Smajor = obj.value("Smajor").toString();
            ui->majorEdit->setText(m_student.Smajor);
        }
        if (obj.contains("Sphone"))
        {
            m_student.Sphone = obj.value("Sphone").toString();
            ui->phoneEdit->setText(m_student.Sphone);
        }
        if (obj.contains("Spassword"))
        {
            m_student.Spassword = obj.value("Spassword").toString();
        }
    }

}



