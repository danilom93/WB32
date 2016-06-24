#ifndef MTEMPCLIENT_H
#define MTEMPCLIENT_H

#include <QIcon>
#include <QSettings>
#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QDateTime>

#include "MClient.h"
#include "clientdefs.h"
#include "NetworkConfig.h"
#include "Login.h"
#include "TimeConf.h"

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

    void on_actionLogout_triggered();

    void notifyConnected();

    void notifyError(QAbstractSocket::SocketError);

    void notifyDisconnected();

    void rxHandler(MClient::BoardAnswer answer);

    void notifyFailure();

    void notifyError();

    void disableActions();

    void enableActions();

    void disableWindow();

    void enableWindow();

    void on_timeRefreshButton_clicked();

    void on_timeSetButton_clicked();

private:

    enum Commands{
        NOCOMM,
        TIMEGET,
        TIMESET
    };

    void timeget();
    void timeset();
    QDateTime parseTimeget(const QString & str);

    Ui::MTempClient * ui;

    bool              m_auth;
    QString           m_addr;
    quint16           m_port;
    QString           m_user;
    QString           m_pass;
    MClient *         m_client;
    Commands          m_currentComm;
};

#endif // MTEMPCLIENT_H
