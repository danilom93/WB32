#include "Loader.h"
#include "ui_Loader.h"

Loader::Loader(const QString & title, QWidget *parent) : QDialog(parent), ui(new Ui::Loader){

    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle(title);

    m_movie = new QMovie(":/ico/img/ajax-loader.gif");
    ui->text->clear();
    ui->loader->setMovie(m_movie);
    movie->start();
}

Loader::~Loader(){

    delete ui;
    delete m_movie;
}

void Loader::setMessage(const QString &msg){

    ui->text->setText(msg);
}
