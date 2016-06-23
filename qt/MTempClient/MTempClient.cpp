#include "MTempClient.h"
#include "ui_MTempClient.h"

MTempClient::MTempClient(QWidget *parent) : QMainWindow(parent), ui(new Ui::MTempClient){

    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/ico/img/Dew Point-64.png"));

    if(!setting.contains(_MTEMP_PORT)){
        setting.setValue(_MTEMP_PORT, _MTEMP_NOPORT);
    }
    if(!setting.contains(_MTEMP_ADDR)){
        setting.setValue(_MTEMP_ADDR, _MTEMP_NOADDR);
    }
    if(!setting.contains(_MTEMP_USER)){
        setting.setValue(_MTEMP_USER, _MTEMP_NOUSER);
    }
    if(!setting.contains(_MTEMP_PASS)){
        setting.setValue(_MTEMP_PASS, _MTEMP_NOPASS);
    }
}

MTempClient::~MTempClient(){

    delete ui;
}

void MTempClient::on_actionConfigura_triggered(){

    NetworkConfig config;

    config.exec();
}
