#ifndef NETWORKCONFIG_H
#define NETWORKCONFIG_H

#include <QIcon>
#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QHostAddress>
#include <QRegExpValidator>
#include <QRegularExpression>

#include "Loader.h"
#include "MClient.h"
#include "MTempDefs.h"
#include "MTempCommons.h"

namespace Ui {

    class NetworkConfig;
}

class NetworkConfig : public QDialog{
    Q_OBJECT

    public:
        explicit NetworkConfig(QWidget *parent = 0);
        ~NetworkConfig();

private slots:
    void on_netKeyShowChecbox_clicked(bool checked);

    void on_netNameLineEdit_textChanged(const QString &arg1);

    void on_netKeyLineEdit_textChanged(const QString &arg1);

    void on_boardIPLineEdit_textChanged(const QString &arg1);

    void on_usernameLineEdit_textChanged(const QString &arg1);

    void on_password1LineEdit_textChanged(const QString &arg1);

    void on_password2LineEdit_textChanged(const QString &arg1);

    void on_boardPortLineEdit_textChanged(const QString &arg1);

    void on_clearButton_clicked();

    void on_abortButton_clicked();

    void on_configureButton_clicked();

    void notifyConnected();

    void notifyError();

    void notifyDisconnected();

    void notifyAnswer();

private:
    void clear();
    void checkAll();

        Ui::NetworkConfig * ui;
        MClient *           m_client;
        QString             m_networkName;
        QString             m_networkKey;
        QString             m_boardIP;
        quint16             m_boardPort;
        QString             m_username;
        QString             m_password1;
        QString             m_password2;
        Loader *            m_loader;
};

#endif // NETWORKCONFIG_H
