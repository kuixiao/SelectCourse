#ifndef COURSE_H
#define COURSE_H

#include <QDialog>
#include <QString>
#include <QNetworkReply>
#include <QTableWidget>

namespace Ui {
class Course;
}

class Course : public QDialog
{
    Q_OBJECT

public:
    explicit Course(QString token, QString userID, int op ,QWidget *parent = 0);
    ~Course();

    bool EmptyLineEdit();
    void initUI();
private slots:
    void addCourse();
    void modifyCourse();
    void replyFinished(QNetworkReply *reply);

    void returnHome();
private:
    QString m_token;
    QString m_userID;
    int m_op;
    Ui::Course *ui;
};

#endif // COURSE_H
