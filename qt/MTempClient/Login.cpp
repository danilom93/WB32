#include "Login.h"
#include "ui_Login.h"

Login::Login(QWidget *parent) : QDialog(parent), ui(new Ui::Login){

    ui->setupUi(this);
}

Login::~Login(){

    delete ui;
}

void Login::on_domaniLineEdit_textChanged(const QString &arg1){

    m_addr = arg1;
}
