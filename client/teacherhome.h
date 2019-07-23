#ifndef TEACHERHOME_H
#define TEACHERHOME_H

#include <QDialog>
#include <QNetworkReply>
#include "personalinfo.h"
#include "modifypersonalinfo.h"
namespace Ui {
class teacherHome;
}

class teacherHome : public QDialog
{
    Q_OBJECT
public:
    explicit teacherHome(QString userID, QString token, QDialog *parent = 0);
    ~teacherHome();

private:
    void initTable();
    void getPersonalInfo();
    void getClassInfo();
    void getPersonalClass();
    void showTableInfo(QJsonValue jsonValue, int show_type = 0);

private slots:
    void getInfo(int index);    //选项卡切换槽函数
    void queryStudentOfClass(); //查看课堂学生按钮槽函数
    void modifyUserInfo();      //修改个人信息按钮槽函数
    void modifyPassword();      //修改密码按钮槽函数
    void modifyClassInfo();     //修改课堂信息按钮槽函数
    void personalInfoReply(QNetworkReply *reply);   //获取个人信息槽函数
    void getClassInfoReply(QNetworkReply *reply);   //获取个人课堂信息响应槽函数
    void getStudentOfClass(QNetworkReply *reply);   //查看学生响应槽函数

private:
    ModifyPersonalInfo *m_modifyPersonalInfo;
    teacherInfo m_teacher;
    Ui::teacherHome *ui;
};

#endif // TEACHERHOME_H


