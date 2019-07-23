#ifndef DEANHOME_H
#define DEANHOME_H

#include <QDialog>
#include <QString>
#include <QNetworkReply>
#include <QTableWidget>
#include "personalinfo.h"
#include "modifypersonalinfo.h"

namespace Ui {
class DeanHome;
}

class DeanHome : public QDialog
{
    Q_OBJECT

public:
    explicit DeanHome(QString userID,QString token,QWidget *parent = 0);
    ~DeanHome();

private:
    void initTable();
    void initTable(QTableWidget *table,QStringList headers, int cloum);
    void setSlots();

    void getPersonalInfo(); //选项卡切换获取个人信息
    void getCourseInfo();   //选项卡切换获取课程信息
    void getClassInfo();  //选项卡切换获取课堂信息
    void getTeacherInfo();  //选项卡切换获取教师信息
    void getStudentInfo();  //选项卡切换获取学生信息

    //表格显示信息
    void showCourseInfo(QJsonValue jsonValue);
    void showClassInfo(QJsonValue jsonValue);
    void showTeacherInfo(QJsonValue jsonValue);
    void showStudentInfo(QJsonValue jsonValue);


private slots:
    void tabSwich(int index);    //选项卡切换槽函数
    void selectItem(int row, int colum);
    //void modifyUserInfo();      //修改个人信息按钮槽函数
    //void modifyPassword();      //修改密码按钮槽函数

    //按钮槽函数
    void modifyDean();
    void modifyPwdDean();

    void addCourse();
    void addClass();
    void addTeacher();
    void addStudent();

    void modifyCourse();
    void modifyClass();
    void modifyTeacher();
    void modifyStudent();

    void deleteCourse();
    void deleteClass();
    void deleteTeacher();
    void deleteStudent();

    // returnJson槽函数
    void replyFinished(QNetworkReply *reply);
    void personalInfoReply(QNetworkReply *reply);   //获取个人信息Json响应槽函数
    void getCourseInfoReply(QNetworkReply *reply);  //获取课程信息Json响应槽函数
    void getClassInfoReply(QNetworkReply *reply);   //获取课堂信息Json响应槽函数
    void getTeacherInfoReply(QNetworkReply *reply);   //获取教师信息Json响应槽函数
    void getStudentInfoReply(QNetworkReply *reply);   //获取学生信息Json响应槽函数

private:

    int m_row;
    int m_colum;
    deanInfo m_dean;
    Ui::DeanHome *ui;
};

#endif // DEANHOME_H
