#ifndef MTEMPCLIENT_H
#define MTEMPCLIENT_H

#include <QIcon>
#include <QSettings>
#include <QMainWindow>

#include "NetworkConfig.h"

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

private:
    Ui::MTempClient *ui;
};

#endif // MTEMPCLIENT_H
