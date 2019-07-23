#ifndef MODIFYPERSONALINFO_H
#define MODIFYPERSONALINFO_H

#include <QDialog>
#include <QNetworkReply>
#include "personalinfo.h"


namespace Ui {
    class modifyPersonalInfo;
}

class ModifyPersonalInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyPersonalInfo(int identity,studentInfo stu, QDialog *parent = 0);
    explicit ModifyPersonalInfo(int identity,teacherInfo tea, QDialog *parent = 0);
    explicit ModifyPersonalInfo(int identity,deanInfo dean, QDialog *parent = 0);

    ~ModifyPersonalInfo();

    bool EmptyInfomation();
    QJsonObject putJsonBody();
private slots:
    void modifyInfo();
    void returnLastUI();
    void replyFinished(QNetworkReply *reply);
protected:
    void getUserInfo();
private:
    QString m_token;
    int m_identity; //此处表示要修改的用户的角色 (学生:0,3; 教师:1,4; 系主任:2)

    Ui::modifyPersonalInfo *ui;
    studentInfo m_student;
    teacherInfo m_teacher;
    deanInfo m_dean;
};

#endif // MODIFYPERSONALINFO_H
