#ifndef MODIFYPASSWORD_H
#define MODIFYPASSWORD_H

#include <QDialog>
#include <QNetworkReply>
namespace Ui {
class ModifyPassword;
}

class ModifyPassword : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyPassword(QString token, QString userID, QWidget *parent = 0);
    ~ModifyPassword();
private slots:
    void updatePwd();
    void returnHome();
    void replyFinished(QNetworkReply *reply);
private:
    QString m_userID;
    QString m_token;
    Ui::ModifyPassword *ui;
};

#endif // MODIFYPASSWORD_H
