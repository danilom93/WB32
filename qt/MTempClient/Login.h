#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QString>
#include <QSettings>

#define _MTEMP_ADDR "ADDR"
#define _MTEMP_PORT "PORT"
#define _MTEMP_USER "USER"
#define _MTEMP_PASS "PASS"

namespace Ui {
    class Login;
}

class Login : public QDialog{

    Q_OBJECT

    public:
        explicit Login(QWidget *parent = 0);
        ~Login();

private slots:
    void on_domaniLineEdit_textChanged(const QString &arg1);

private:
        Ui::Login * ui;
        QString     m_addr;
        QString     m_port;
        QString     m_user;
        QString     m_pass;
};

#endif // LOGIN_H
