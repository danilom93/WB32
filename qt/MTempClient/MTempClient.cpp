#include "MTempClient.h"
#include "ui_MTempClient.h"

#define SEP     (QString(_MTEMP_SEP))
#define USRPSW  (m_user + SEP + m_pass + SEP)


MTempClient::MTempClient(QWidget *parent) : QMainWindow(parent), ui(new Ui::MTempClient), m_auth(false), m_currentComm(NOCOMM){

    QSettings setting;
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

    m_client = new MClient(this);

    enableActions();
    disableWindow();

    connect(m_client, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(notifyError(QAbstractSocket::SocketError)));
    connect(m_client, SIGNAL(connected()),
            this, SLOT(notifyConnected()));
    connect(m_client, SIGNAL(answerReceived(MClient::BoardAnswer)),
            this, SLOT(rxHandler(MClient::BoardAnswer)));
    connect(m_client, SIGNAL(disconnected()),
            this, SLOT(notifyDisconnected()));

}

MTempClient::~MTempClient(){

    delete ui;
}

void MTempClient::on_actionConfigura_triggered(){

    NetworkConfig config;

    config.exec();
}

void MTempClient::on_actionLogin_triggered(){

    Login login;

    login.exec();

    if(login.good()){
        disableActions();
        m_addr = login.address();
        m_port = login.port();
        m_user = login.username();
        m_pass = login.password();

        m_client->setAddress(m_addr);
        m_client->setPort(m_port);
        m_client->connectToHost();
    }
}

void MTempClient::on_actionLogout_triggered(){

    m_client->disconnectFromHost();
}

void MTempClient::notifyConnected(){

    m_auth = true;
    enableWindow();
}

void MTempClient::notifyError(QAbstractSocket::SocketError){

    QMessageBox::critical(this, "Errore", m_client->lastError());
    m_auth = false;
    disableWindow();
    enableActions();
}

void MTempClient::notifyDisconnected(){

    m_auth = false;
    disableWindow();
    enableActions();
}

void MTempClient::rxHandler(MClient::BoardAnswer answer){

    QString     str;
    QTime       time;
    QDate       data;
    QDateTime   dateTime;
    QStringList list;

    if(answer == MClient::BoardAnswer::Fail){
        m_client->bufferClear();
        notifyFailure();
        m_currentComm = NOCOMM;
        return;
    }
    if(answer == MClient::BoardAnswer::Error){
        m_client->bufferClear();
        notifyError();
        m_currentComm = NOCOMM;
        return;
    }

    str = m_client->dataReceived();

    //str.remove(SEP + QString(_MTEMP_BOARD_OK));

    switch (m_currentComm) {
        case TIMEGET:
            // 0  1  2  3  4  5  6
            //AA*MM*GG*WD*HH*MM*SS*
            qDebug() << str;
            list = str.split("*");
            m_client->bufferClear();
            data.setDate(list[0].toInt(), list[1].toInt(), list[2].toInt());
            time.setHMS(list[4].toInt(), list[5].toInt(), list[6].toInt());
            QMessageBox::information(this, "Ora centralina", data.toString("dd.MM.yyyy") +
                                                             QString(" ") +
                                                             time.toString("hh:mm:ss"));
            break;
        default:
            break;
    }
    m_currentComm = NOCOMM;
}

void MTempClient::notifyFailure(){

    QMessageBox::critical(this, this->windowTitle(), "Errore centralina.");
    notifyDisconnected();
}

void MTempClient::notifyError(){

    QMessageBox::critical(this, this->windowTitle(), "Errore nel login: username o password errati");
    notifyDisconnected();
}

void MTempClient::disableActions(){

    ui->actionLogin->setEnabled(false);
    ui->actionConfigura->setEnabled(false);
    ui->actionLogout->setEnabled(true);
    ui->actionInfo_Ora->setEnabled(true);
}

void MTempClient::enableActions(){

    ui->actionLogin->setEnabled(true);
    ui->actionConfigura->setEnabled(true);
    ui->actionLogout->setEnabled(false);
    ui->actionInfo_Ora->setEnabled(false);
}

void MTempClient::disableWindow(){

    qDebug() << "void MTempClient::disableWindow() da implementare";
}

void MTempClient::enableWindow(){

    qDebug() << "void MTempClient::enableWindow() da implementare";
}


void MTempClient::on_actionInfo_Ora_triggered(){

    m_currentComm = TIMEGET;
    m_client->waitFor(_MTEMP_BOARD_OK);
    m_client->write(USRPSW + QString(_MTEMP_TIMEGET));
}
