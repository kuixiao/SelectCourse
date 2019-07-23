#ifndef MODIFYSTUDENTINFO_H
#define MODIFYSTUDENTINFO_H

#include <QDialog>
#include "studenthome.h"

namespace Ui {
class ModifyStudentInfo;
}

class ModifyStudentInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyStudentInfo(QWidget *parent = 0);
    ~ModifyStudentInfo();

    bool EmptyInfomation();
private slots:
    void modifyInfo();
    void returnLastUI();
protected:
    void getUserInfo();
private:
    Ui::ModifyStudentInfo *ui;
};

#endif // MODIFYSTUDENTINFO_H
