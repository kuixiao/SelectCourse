#ifndef STUDENTHOME_H
#define STUDENTHOME_H

#include <QDialog>
#include <QNetworkReply>
#include "personalinfo.h"
#include "modifypersonalinfo.h"

namespace Ui {
class StudentHome;
}


class StudentHome : public QDialog
{
    Q_OBJECT

public:
    explicit StudentHome(QString userID, QString token, QDialog *parent = 0);
    ~StudentHome();

private:
    void getPersonalInfo();
    void getCourseInfo();
    void getPersonalClass();
    void showTableInfo(QJsonValue jsonValue, int show_type);

private slots:
    void getInfo(int index);    //选项卡切换槽函数
    void selectCourse();        //选课按钮槽函数
    void withdrawal();          //退选按钮槽函数
    void modifyUserInfo();      //修改个人信息按钮槽函数
    void modifyPassword();
    void personalInfoReply(QNetworkReply *reply);           //获取个人结果信息槽函数
    void getPersonalClassInfoReply(QNetworkReply *reply);   //获取个人选课结果信息槽函数
    void getCourseInfoReply(QNetworkReply *reply);          //获取可选的课堂信息槽函数
    void replyFinished(QNetworkReply *reply);   //选课响应槽函数
private:
    Ui::StudentHome *ui;
public:
    studentInfo m_student;

};

#endif // STUDENTHOME_H
