#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QNetworkReply>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(int identity, QWidget *parent = 0);
    ~Register();
private slots:
    void registerCommit();  //提交注册请求
    void returnLoginUI();   //返回登录界面
    bool EmptyInfomation(); //判断必填信息是否存在空项
    void replyFinished(QNetworkReply *reply);
private:
    int m_identity;
    Ui::Register *ui;
};

#endif // REGISTER_H
