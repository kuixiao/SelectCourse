#include "classdata.h"
#include "ui_classdata.h"
#include <QUrl>
#include <QByteArray>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QHttpMultiPart>

#include "jsontools.h"
ClassData::ClassData(QString token, QString userID, int op,
                     QStringList tno, QStringList tname, QStringList cno, QStringList cname, QStringList classdata, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::ClassData)
{
    m_token = token;
    m_userID = userID;
    m_op = op;

    m_Tno = tno;
    m_Tname = tname;
    m_Cno = cno;
    m_Cname = cname;
    ui->setupUi(this);
    if (m_op == 0)
    {
        qDebug()<<"增加课堂"<<endl;
        ui->titleLabel->setText("增加课堂");
        for(int i = 0; i < m_Cno.size(); ++i)
        {
            //qDebug()<<m_Cno.size()<<endl;
            ui->courseBox->addItem(m_Cno.at(i));
        }
        ui->courseBox->setCurrentIndex(0);
        ui->CnameEdit->setText(m_Cname.at(0));

        for(int i = 0; i < m_Tno.size(); ++i)
        {
            ui->teacherBox->insertItem(i,m_Tno.at(i));
        }
        ui->teacherBox->setCurrentIndex(0);
        ui->TnameEdit->setText(m_Tname.at(0));
        connect(ui->commitBtn, SIGNAL(clicked()), this, SLOT(addClass()));
    }
    else if (m_op == 1)
    {
        qDebug()<<"修改课堂"<<endl;
        ui->titleLabel->setText("修改课堂");
        for(int i = 0; i < m_Tno.size(); ++i)
        {
            qDebug()<<m_Tno.at(i)<<endl;
            ui->teacherBox->insertItem(i,m_Tno.at(i));
        }

        for(int i = 0; i < m_Tname.size(); ++i)
        {

            if (m_Tname.at(i) == classdata.at(7))
            {
                qDebug()<<m_Tname.at(i)<<endl;
                ui->teacherBox->setCurrentIndex(i);
                break;
            }
        }

        ui->TnameEdit->setText(classdata.at(7));

        ui->courseBox->setCurrentText(classdata.at(0));
        ui->CnameEdit->setText(classdata.at(2));
        ui->CnumberEdit->setText(classdata.at(1));
        ui->CtimeEdit->setText(classdata.at(3));
        ui->CsessionEdit->setText(classdata.at(4));
        ui->CaddressEdit->setText(classdata.at(5));
        ui->CsumEdit->setText(classdata.at(6));
        connect(ui->commitBtn, SIGNAL(clicked()), this, SLOT(modifyClass()));
    }
    connect(ui->returnBtn, SIGNAL(clicked()), this, SLOT(returnHome()));

    connect(ui->courseBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setCourseContents(int)));
    connect(ui->teacherBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setTeacherContents(int)));

}

ClassData::~ClassData()
{
    delete ui;
}

bool ClassData::EmptyLineEdit()
{
    if (ui->CnameEdit->text().isEmpty())return false;
    if (ui->CsessionEdit->text().isEmpty())return false;
    if (ui->CtimeEdit->text().isEmpty())return false;
    if (ui->CsumEdit->text().isEmpty())return false;
    if (ui->CaddressEdit->text().isEmpty())return false;
    if (ui->TnameEdit->text().isEmpty())return false;
    return true;
}

//增加课堂槽函数
void ClassData::addClass()
{
    if (!EmptyLineEdit())  //判断是否存在未填信息项
    {
        QMessageBox::warning(this, "warning","信息不能为空");
        return;
    }

    QJsonObject json;
    json.insert("Cno", ui->courseBox->currentText().trimmed());
    json.insert("Csum", ui->CsumEdit->text().trimmed().toInt());
    json.insert("Csession", ui->CsessionEdit->text().trimmed());
    json.insert("Caddress", ui->CaddressEdit->text().trimmed());
    json.insert("Ctime", ui->CtimeEdit->text().trimmed());
    json.insert("Tno", ui->teacherBox->currentText().trimmed());
    QUrl url("http://127.0.0.1:8080/api/dean/add/class/" + m_userID);

    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);
    QNetworkRequest request = JsonTools::getJsonHeader(m_token, url);// 构造请求
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    // 发送请求
    manager->post(request, dataArray);
}

//修改课堂信息
void ClassData::modifyClass()
{
    qDebug()<<"修改课堂信息"<<endl;
    if (!EmptyLineEdit())  //判断是否存在未填信息项
    {
        QMessageBox::warning(this, "warning","信息不能为空");
        return;
    }

    QJsonObject json;
    json.insert("Cnumber", ui->CnumberEdit->text().trimmed());
    json.insert("Csum", ui->CsumEdit->text().trimmed().toInt());
    json.insert("Csession", ui->CsessionEdit->text().trimmed());
    json.insert("Caddress", ui->CaddressEdit->text().trimmed());
    json.insert("Ctime", ui->CtimeEdit->text().trimmed());
    json.insert("Tno", ui->teacherBox->currentText().trimmed());
    QUrl url("http://127.0.0.1:8080/api/dean/update/class/" + m_userID);

    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);
    QNetworkRequest request = JsonTools::getJsonHeader(m_token, url);// 构造请求
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    // 发送请求
    manager->put(request, dataArray);
}

//解析响应json数据
void ClassData::replyFinished(QNetworkReply *reply)
{
    JsonTools::replyFinished(reply);
}

//返回上一个界面
void ClassData::returnHome()
{
    this->close();
}

//设置comBox内容
void ClassData::setCourseContents(int index)
{
    ui->CnameEdit->setText(m_Cname.at(index));
}
void ClassData::setTeacherContents(int index)
{
    ui->TnameEdit->setText(m_Tname.at(index));
}

