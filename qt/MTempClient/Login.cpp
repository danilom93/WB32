#include "Login.h"
#include "ui_Login.h"
#include <QDebug>

Login::Login(QWidget *parent) : QDialog(parent), ui(new Ui::Login){

    QSettings setting;
    QRegExp portRx("^(?:6553[0-5]|655[0-2][0-9]|65[0-4][0-9]{2}|6[0-4][0-9]{3}|[1-5][0-9]{4}|[1-9][0-9]{1,3}|[1-9])$");
    QRegExpValidator * portValidator = new QRegExpValidator(portRx, this);

    ui->setupUi(this);

    ui->portLineEdit->setValidator(portValidator);

    this->setWindowTitle("Login");
    this->setWindowIcon(QIcon(":/ico/img/Key-48.png"));

    if(setting.value(_MTEMP_ADDR).toString() != _MTEMP_NOADDR){

        ui->domaniLineEdit->setText(setting.value(_MTEMP_ADDR).toString());
        ui->remeberNetCheck->setChecked(true);
    }
    if(setting.value(_MTEMP_PORT).toUInt()   != _MTEMP_NOPORT){

        ui->portLineEdit->setText(setting.value(_MTEMP_PORT).toString());
    }
    if(setting.value(_MTEMP_USER).toString() != _MTEMP_NOUSER){

        ui->usernameLineEdit->setText(setting.value(_MTEMP_USER).toString());
        ui->rememberUserCheck->setChecked(true);
    }
    qDebug() << setting.value(_MTEMP_PASS).toString();
    if(setting.value(_MTEMP_PASS).toString() != _MTEMP_NOPASS){

        ui->passwordLineEdit->setText(setting.value(_MTEMP_PASS).toString());
    }

}

Login::~Login(){

    delete ui;
}

void Login::on_domaniLineEdit_textChanged(const QString &arg1){

    QRegExp rx;
    QSettings setting;
    QString rxPattern = "[\[]| |[\]]";

    rx.setPattern(rxPattern);
    rx.setCaseSensitivity(Qt::CaseInsensitive);

    if(arg1.contains(rx)){

        QMessageBox::critical(this, this->windowTitle(), "L'indirizzo non può contenere [, ], o spazi vuoti.");

        ui->domaniLineEdit->clear();
        return;
    }

    if(ui->remeberNetCheck->isChecked()){

        setting.setValue(_MTEMP_ADDR, arg1);
    }else{

        setting.setValue(_MTEMP_ADDR, _MTEMP_NOADDR);
        setting.setValue(_MTEMP_PORT, _MTEMP_NOPORT);
    }
    m_addr = arg1;
}

void Login::on_portLineEdit_textChanged(const QString &arg1){

    QSettings setting;
    m_port = arg1;

    if(ui->remeberNetCheck->isChecked()){

        setting.setValue(_MTEMP_PORT, arg1.toUInt());
    }else{

        setting.setValue(_MTEMP_ADDR, _MTEMP_NOADDR);
        setting.setValue(_MTEMP_PORT, _MTEMP_NOPORT);
    }

}

void Login::on_usernameLineEdit_textChanged(const QString &arg1){

    QRegExp rx;
    QSettings setting;
    QString rxPattern = "[\[]| |[\]]";

    rx.setPattern(rxPattern);
    rx.setCaseSensitivity(Qt::CaseInsensitive);

    if(arg1.contains(rx)){

        QMessageBox::critical(this, this->windowTitle(), "Il nome utente non può contenere [, ], o spazi vuoti.");

        ui->usernameLineEdit->clear();
        return;
    }
    if(ui->rememberUserCheck->isChecked()){

        setting.setValue(_MTEMP_USER, arg1);
    }else{

        setting.setValue(_MTEMP_USER, _MTEMP_NOUSER);
        setting.setValue(_MTEMP_PASS, _MTEMP_NOPASS);
    }
    m_user = arg1;
}

void Login::on_passwordLineEdit_textChanged(const QString &arg1){

    QRegExp rx;
    QSettings setting;
    QString rxPattern = "[\[]| |[\]]";

    rx.setPattern(rxPattern);
    rx.setCaseSensitivity(Qt::CaseInsensitive);

    if(arg1.contains(rx)){

        QMessageBox::critical(this, this->windowTitle(), "La password non può contenere [, ], o spazi vuoti.");

        ui->usernameLineEdit->clear();
        return;
    }
    if(ui->rememberUserCheck->isChecked()){

        setting.setValue(_MTEMP_PASS, arg1);
    }else{

        setting.setValue(_MTEMP_USER, _MTEMP_NOUSER);
        setting.setValue(_MTEMP_PASS, _MTEMP_NOPASS);
    }
    m_pass = arg1;
}
