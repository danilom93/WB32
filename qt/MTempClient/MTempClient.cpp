#include "MTempClient.h"
#include "ui_MTempClient.h"

MTempClient::MTempClient(QWidget *parent) : QMainWindow(parent), ui(new Ui::MTempClient){

    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/ico/img/Dew Point-64.png"));
}

MTempClient::~MTempClient(){

    delete ui;
}

void MTempClient::on_actionConfigura_triggered(){

    NetworkConfig config;

    config.exec();
}
