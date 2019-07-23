#ifndef MODIFYCLASSINFO_H
#define MODIFYCLASSINFO_H

#include <QDialog>
#include "personalinfo.h"
#include <QNetworkReply>

namespace Ui {
class ModifyClassInfo;
}

class ModifyClassInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyClassInfo(int identity, QStringList classinfo, QString token, QString userID,QWidget *parent = 0);
    ~ModifyClassInfo();

    bool EmpthEdit();
private slots:
    void modifyClass();

    void returnHome();

    void replyFinished(QNetworkReply *reply);
private:
    Ui::ModifyClassInfo *ui;
    ClassInfo m_classInfo;
    QString m_token;
    QString m_userID;
    int m_identity;
};

#endif // MODIFYCLASSINFO_H
