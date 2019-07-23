#ifndef PERSONALINFO_H
#define PERSONALINFO_H

#include <QString>
#include <QStringList>
class PersonalInfo
{
public:
    QString Identity;
    QString Token;
};

class studentInfo: public virtual PersonalInfo
{
public:
    QString Sno;
    QString Sname;
    QString Ssex;
    QString Sclass;
    QString Smajor;
    QString Sbirthday;
    QString Sphone;
    QString Spassword;
    studentInfo operator =(studentInfo stu)
    {
        this->Identity = stu.Identity;
        this->Token = stu.Token;
        this->Sno = stu.Sno;
        this->Sname = stu.Sname;
        this->Ssex = stu.Ssex;
        this->Sclass = stu.Sclass;
        this->Smajor = stu.Smajor;
        this->Sbirthday = stu.Sbirthday;
        this->Sphone = stu.Sphone;
        this->Spassword = stu.Spassword;
        return *this;
    }
};

class teacherInfo:  public virtual PersonalInfo
{
public:
    QString Tno;
    QString Tname;
    QString Tsex;
    QString Tclass;
    QString Tmajor;
    QString Tbirthday;
    QString Tphone;
    QString Tpassword;
    teacherInfo operator =(teacherInfo stu)
    {
        this->Identity = stu.Identity;
        this->Token = stu.Token;
        this->Tno = stu.Tno;
        this->Tname = stu.Tname;
        this->Tsex = stu.Tsex;
        this->Tclass = stu.Tclass;
        this->Tmajor = stu.Tmajor;
        this->Tbirthday = stu.Tbirthday;
        this->Tphone = stu.Tphone;
        this->Tpassword = stu.Tpassword;
        return (*this);
    }
};

class deanInfo:  public virtual PersonalInfo
{
public:
    QString Dno;
    QString Dname;
    QString Dsex;
    QString Dclass;
    QString Dmajor;
    QString Dbirthday;
    QString Dphone;
    QString Dpassword;
    deanInfo operator =(deanInfo dean)
    {
        this->Identity = dean.Identity;
        this->Token = dean.Token;
        this->Dno = dean.Dno;
        this->Dname = dean.Dname;
        this->Dsex = dean.Dsex;
        this->Dclass = dean.Dclass;
        this->Dmajor = dean.Dmajor;
        this->Dbirthday = dean.Dbirthday;
        this->Dphone = dean.Dphone;
        this->Dpassword = dean.Dpassword;
        return (*this);
    }
};

class CourseInfo
{
public:
    QString Cno;        //课程代码
    QString Cname;      //课程名称
    QString Ccredit;    //学分
    QString Chour;      //学时
    QString Ctype;      //课程类型
    QString Cdept;      //开课院系
    CourseInfo* operator =(QStringList courseInfo)
    {
        this->Cno = courseInfo.at(0);
        this->Cname = courseInfo.at(1);
        this->Ccredit = courseInfo.at(2);
        this->Chour = courseInfo.at(3);
        this->Ctype = courseInfo.at(4);
        this->Cdept = courseInfo.at(5);
        return this;
    }
};

class ClassInfo
{
public:
    QString Cnumber;
    QString Cname;
    QString Ccredit;
    QString Chour;
    QString Ctype;
    QString Cdept;
    QString Ctime;
    QString Csession;
    QString Caddress;
    int Csum;
    ClassInfo operator =(QStringList calssInfo)
    {
        this->Cnumber = calssInfo.at(0);
        this->Cname = calssInfo.at(1);
        this->Ccredit = calssInfo.at(2);
        this->Chour = calssInfo.at(3);
        this->Ctype = calssInfo.at(4);
        this->Cdept = calssInfo.at(5);
        this->Ctime = calssInfo.at(6);
        this->Csession = calssInfo.at(7);
        this->Caddress = calssInfo.at(8);
        this->Csum = calssInfo.at(9).toInt();
        return (*this);
    }
};



#endif // PERSONALINFO_H
