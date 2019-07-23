#ifndef CLASSINFO_H
#define CLASSINFO_H

#include <QDialog>
#include <QStringList>
#include <QMap>
#include <QNetworkReply>

namespace Ui {
class ClassData;
}

class ClassData : public QDialog
{
    Q_OBJECT

public:
    explicit ClassData(QString token, QString userID, int op,  QStringList tno,
        QStringList tname, QStringList cno, QStringList cname, QStringList classdata, QWidget *parent = 0);

    ~ClassData();

private:
    bool EmptyLineEdit();
private slots:
    void replyFinished(QNetworkReply *reply);
    void returnHome();
    void addClass();
    void modifyClass();

    void setCourseContents(int index);
    void setTeacherContents(int index);
private:
    QString m_token;
    QString m_userID;
    int m_op;
    QStringList m_Tno;
    QStringList m_Tname;
    QStringList m_Cno;
    QStringList m_Cname;
    Ui::ClassData *ui;
};

#endif // CLASSINFO_H
