#include "MTempClient.h"
#include "ui_MTempClient.h"

MTempClient::MTempClient(QWidget *parent) : QMainWindow(parent), ui(new Ui::MTempClient){

    ui->setupUi(this);
}

MTempClient::~MTempClient(){

    delete ui;
}
