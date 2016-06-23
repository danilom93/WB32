#ifndef MTEMPCLIENT_H
#define MTEMPCLIENT_H

#include <QIcon>
#include <QSettings>
#include <QMainWindow>

#include "clientdefs.h"
#include "NetworkConfig.h"
#include "Login.h"

namespace Ui {

    class MTempClient;
}

class MTempClient : public QMainWindow{
    Q_OBJECT

public:
    explicit MTempClient(QWidget *parent = 0);
    ~MTempClient();

private slots:
    void on_actionConfigura_triggered();

    void on_actionLogin_triggered();

private:
    Ui::MTempClient *ui;
};

#endif // MTEMPCLIENT_H
