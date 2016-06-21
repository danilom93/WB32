#ifndef MTEMPCLIENT_H
#define MTEMPCLIENT_H

#include <QMainWindow>

namespace Ui {

    class MTempClient;
}

class MTempClient : public QMainWindow{
    Q_OBJECT

public:
    explicit MTempClient(QWidget *parent = 0);
    ~MTempClient();

private:
    Ui::MTempClient *ui;
};

#endif // MTEMPCLIENT_H
