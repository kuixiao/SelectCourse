#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkReply>
#include "register.h"
#include "studenthome.h"
#include "teacherhome.h"
#include "deanhome.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void replyFinished(QNetworkReply *reply);
    void userLogin();
    void userRegister();



private:
    Ui::Widget *ui;
    Register *m_register;
    StudentHome *m_studentHome;
    teacherHome *m_teacherHome;
    DeanHome *m_deanHome;
    QString m_userID;

};

#endif // WIDGET_H
