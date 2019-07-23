#include "widget.h"
#include "ui_widget.h"
#include "customtabstyle.h"

#include <QUrl>
#include <QByteArray>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>

class CustomTabStyle;
int identity = 0;
QString Token;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    m_studentHome = nullptr;
    m_register = nullptr;
    ui->setupUi(this);
    ui->tabWidget->setTabText(0,"Student");
    ui->tabWidget->setTabText(1,"Teacher");
    ui->tabWidget->setTabText(2,"Dean");
    ui->tabWidget->setTabPosition(QTabWidget::North);
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle(100, 30));

    connect(ui->loginBtn,SIGNAL(clicked()),this,SLOT(userLogin()));
    connect(ui->loginBtn_2,SIGNAL(clicked()),this,SLOT(userLogin()));
    connect(ui->loginBtn_3,SIGNAL(clicked()),this,SLOT(userLogin()));

    connect(ui->registerBtn,SIGNAL(clicked()),this,SLOT(userRegister()));
    connect(ui->registerBtn_2,SIGNAL(clicked()),this,SLOT(userRegister()));
    connect(ui->registerBtn_3,SIGNAL(clicked()),this,SLOT(userRegister()));
}

Widget::~Widget()
{
    delete ui;
}

//用户登录响应槽函数
void Widget::replyFinished(QNetworkReply *reply)
{
    // 获取响应信息
    QByteArray bytes = reply->readAll();

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(bytes, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << QStringLiteral("解析Json失败");
        return;
    }

    // 解析Json
    if (doucment.isObject())
    {
        QJsonObject obj = doucment.object();
        if ( !obj.contains("code") || !obj.contains("msg") || !obj.contains("token"))
        {
            QMessageBox::information(this,"login result:","错误的Json格式");
        }

        QJsonValue value[3];
        value[0] = obj.take("code");
        value[1] = obj.take("msg");
        value[2] = obj.take("token");
        Token = value[2].toString();
        QMessageBox::information(this,"login result:","code:" +
                 QString::number(value[0].toInt()) + "\nmsg:" +
                 value[1].toString() + "\ntoken:" + value[2].toString());
        if (value[0].toInt() == 0)
        {
            this->close();
            if (identity == 0)
            {
                m_studentHome = new StudentHome(m_userID,Token);
                m_studentHome->show();
                m_studentHome->exec();
            }
            else if (identity == 1)
            {
                m_teacherHome = new teacherHome(m_userID,Token);
                m_teacherHome->show();
                m_teacherHome->exec();
            }
            else if (identity == 2)
            {
                m_deanHome = new DeanHome(m_userID, Token);
                m_deanHome->show();
                m_deanHome->exec();
            }
        }
    }
    else
    {
        QMessageBox::warning(this,"login result:","错误的Json格式");
    }
}

//用户登录按钮槽函数
void Widget::userLogin()
{
    QUrl url("http://127.0.0.1:8080/api/login");
    QJsonObject json;
    identity = ui->tabWidget->currentIndex();
    QString account;
    QString password;
    if (identity == 0)
    {
        account = ui->SaccountEdit->text();
        password = ui->SpasswordEdit->text();
    }
    else if (identity == 1)
    {
        account = ui->TaccountEdit->text();
        password = ui->TpasswordEdit->text();
    }
    else if (identity == 2)
    {
        account = ui->DaccountEdit->text();
        password = ui->DpasswordEdit->text();
    }

    if (account.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this,"login result:","账号密码不能为空");
    }
    m_userID = account;
    qDebug()<<"account:"<<account<<endl<<"password:"<<password<<endl;

    json.insert("UserName", account);
    json.insert("Pwd", password);
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

//用户注册按钮槽函数
void Widget::userRegister()
{
    identity = ui->tabWidget->currentIndex();
    this->close();
    m_register = new Register(identity);
    m_register->show();
    m_register->exec();
    this->show();

}

