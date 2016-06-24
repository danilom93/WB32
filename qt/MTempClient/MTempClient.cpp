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

    str.remove(SEP + QString(_MTEMP_BOARD_OK));

    switch (m_currentComm) {
        case TIMEGET:
            ui->dateTimeEdit->setDateTime(parseTimeget(str));
            m_client->bufferClear();
            break;
        case TIMESET:
            QMessageBox::information(this, this->windowTitle(), "Ora impostata correttamente.");
            m_client->bufferClear();
            break;
        default:
            break;
    }
    m_currentComm = NOCOMM;

    enableWindow();
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
}

void MTempClient::enableActions(){

    ui->actionLogin->setEnabled(true);
    ui->actionConfigura->setEnabled(true);
    ui->actionLogout->setEnabled(false);
}

void MTempClient::disableWindow(){

    ui->dateTimeEdit->setEnabled(false);
    ui->timeSetButton->setEnabled(false);
    ui->timeRefreshButton->setEnabled(false);

    ui->configButton_1->setEnabled(false);
    ui->configButton_2->setEnabled(false);
    ui->configButton_3->setEnabled(false);
    ui->configButton_4->setEnabled(false);
    ui->configButton_5->setEnabled(false);
    ui->configButton_6->setEnabled(false);
    ui->configButton_7->setEnabled(false);
    ui->configButton_8->setEnabled(false);

    ui->updateButton_1->setEnabled(false);
    ui->updateButton_2->setEnabled(false);
    ui->updateButton_3->setEnabled(false);
    ui->updateButton_4->setEnabled(false);
    ui->updateButton_5->setEnabled(false);
    ui->updateButton_6->setEnabled(false);
    ui->updateButton_7->setEnabled(false);
    ui->updateButton_8->setEnabled(false);

    ui->forceOffButton_1->setEnabled(false);
    ui->forceOffButton_2->setEnabled(false);
    ui->forceOffButton_3->setEnabled(false);
    ui->forceOffButton_4->setEnabled(false);
    ui->forceOffButton_5->setEnabled(false);
    ui->forceOffButton_6->setEnabled(false);
    ui->forceOffButton_7->setEnabled(false);
    ui->forceOffButton_8->setEnabled(false);

    ui->forceOnButton_1->setEnabled(false);
    ui->forceOnButton_2->setEnabled(false);
    ui->forceOnButton_3->setEnabled(false);
    ui->forceOnButton_4->setEnabled(false);
    ui->forceOnButton_5->setEnabled(false);
    ui->forceOnButton_6->setEnabled(false);
    ui->forceOnButton_7->setEnabled(false);
    ui->forceOnButton_8->setEnabled(false);

    ui->setAutoButton_1->setEnabled(false);
    ui->setAutoButton_2->setEnabled(false);
    ui->setAutoButton_3->setEnabled(false);
    ui->setAutoButton_4->setEnabled(false);
    ui->setAutoButton_5->setEnabled(false);
    ui->setAutoButton_6->setEnabled(false);
    ui->setAutoButton_7->setEnabled(false);
    ui->setAutoButton_8->setEnabled(false);

    ui->temperatureEdit_1->setEnabled(false);
    ui->temperatureEdit_2->setEnabled(false);
    ui->temperatureEdit_3->setEnabled(false);
    ui->temperatureEdit_4->setEnabled(false);
    ui->temperatureEdit_5->setEnabled(false);
    ui->temperatureEdit_6->setEnabled(false);
    ui->temperatureEdit_7->setEnabled(false);
    ui->temperatureEdit_8->setEnabled(false);

    ui->statusLineEdit_1->setEnabled(false);
    ui->statusLineEdit_2->setEnabled(false);
    ui->statusLineEdit_3->setEnabled(false);
    ui->statusLineEdit_4->setEnabled(false);
    ui->statusLineEdit_5->setEnabled(false);
    ui->statusLineEdit_6->setEnabled(false);
    ui->statusLineEdit_7->setEnabled(false);
    ui->statusLineEdit_8->setEnabled(false);
}

void MTempClient::enableWindow(){

    ui->dateTimeEdit->setEnabled(true);
    ui->timeSetButton->setEnabled(true);
    ui->timeRefreshButton->setEnabled(true);

    ui->configButton_1->setEnabled(true);
    ui->configButton_2->setEnabled(true);
    ui->configButton_3->setEnabled(true);
    ui->configButton_4->setEnabled(true);
    ui->configButton_5->setEnabled(true);
    ui->configButton_6->setEnabled(true);
    ui->configButton_7->setEnabled(true);
    ui->configButton_8->setEnabled(true);

    ui->updateButton_1->setEnabled(true);
    ui->updateButton_2->setEnabled(true);
    ui->updateButton_3->setEnabled(true);
    ui->updateButton_4->setEnabled(true);
    ui->updateButton_5->setEnabled(true);
    ui->updateButton_6->setEnabled(true);
    ui->updateButton_7->setEnabled(true);
    ui->updateButton_8->setEnabled(true);

    ui->forceOffButton_1->setEnabled(true);
    ui->forceOffButton_2->setEnabled(true);
    ui->forceOffButton_3->setEnabled(true);
    ui->forceOffButton_4->setEnabled(true);
    ui->forceOffButton_5->setEnabled(true);
    ui->forceOffButton_6->setEnabled(true);
    ui->forceOffButton_7->setEnabled(true);
    ui->forceOffButton_8->setEnabled(true);

    ui->forceOnButton_1->setEnabled(true);
    ui->forceOnButton_2->setEnabled(true);
    ui->forceOnButton_3->setEnabled(true);
    ui->forceOnButton_4->setEnabled(true);
    ui->forceOnButton_5->setEnabled(true);
    ui->forceOnButton_6->setEnabled(true);
    ui->forceOnButton_7->setEnabled(true);
    ui->forceOnButton_8->setEnabled(true);

    ui->setAutoButton_1->setEnabled(true);
    ui->setAutoButton_2->setEnabled(true);
    ui->setAutoButton_3->setEnabled(true);
    ui->setAutoButton_4->setEnabled(true);
    ui->setAutoButton_5->setEnabled(true);
    ui->setAutoButton_6->setEnabled(true);
    ui->setAutoButton_7->setEnabled(true);
    ui->setAutoButton_8->setEnabled(true);

    ui->temperatureEdit_1->setEnabled(true);
    ui->temperatureEdit_2->setEnabled(true);
    ui->temperatureEdit_3->setEnabled(true);
    ui->temperatureEdit_4->setEnabled(true);
    ui->temperatureEdit_5->setEnabled(true);
    ui->temperatureEdit_6->setEnabled(true);
    ui->temperatureEdit_7->setEnabled(true);
    ui->temperatureEdit_8->setEnabled(true);

    ui->statusLineEdit_1->setEnabled(true);
    ui->statusLineEdit_2->setEnabled(true);
    ui->statusLineEdit_3->setEnabled(true);
    ui->statusLineEdit_4->setEnabled(true);
    ui->statusLineEdit_5->setEnabled(true);
    ui->statusLineEdit_6->setEnabled(true);
    ui->statusLineEdit_7->setEnabled(true);
    ui->statusLineEdit_8->setEnabled(true);
}

void MTempClient::timeget(){

    /*
     *  FORMATO STRINGA TIMEGET
     *  (CLIENT)        username*password*[TIMEGET]
     *  (SERVER)        (AA*MM*GG*WD*HH*MM*SS*[OK] || [FAIL] || [ERROR])
     */
    disableWindow();
    m_currentComm = TIMEGET;
    m_client->waitFor(_MTEMP_BOARD_OK);
    m_client->write(USRPSW + QString(_MTEMP_TIMEGET));
}

void MTempClient::timeset(){

    /*
     *  FORMATO STRINGA TIMESET
     *  (CLIENT)        username*password*AA*MM*GG*WD*HH*MM*SS*[TIMESET]
     */
    QString str;
    QDateTime curr = ui->dateTimeEdit->dateTime();
    int y = curr.date().year() - 2000;
    int m = curr.date().month();
    int d = curr.date().day();
    int w = (curr.date().dayOfWeek() == 7 ? 1 : (1 + curr.date().dayOfWeek()));
    int hh = curr.time().hour();
    int mm = curr.time().minute();

    str += (QString::number(y)  + SEP);
    str += (QString::number(m)  + SEP);
    str += (QString::number(d)  + SEP);
    str += (QString::number(w)  + SEP);
    str += (QString::number(hh) + SEP);
    str += (QString::number(mm) + SEP);
    str += (QString::number(0)  + SEP);

    disableWindow();
    m_currentComm = TIMESET;

    m_client->waitFor(_MTEMP_BOARD_OK);
    m_client->write(USRPSW + str + QString(_MTEMP_TIMESET));
    qDebug() << str;
}

QDateTime MTempClient::parseTimeget(const QString &str){

    QDate date;
    QTime time;
    QDateTime res;
    QStringList list = str.split("*");
    date.setDate(2000 + list[0].toInt(), list[1].toInt(), list[2].toInt());
    time.setHMS(list[4].toInt(), list[5].toInt(), list[6].toInt());

    res.setTime(time);
    res.setDate(date);

    return res;
}

void MTempClient::on_timeRefreshButton_clicked(){

    timeget();
}

void MTempClient::on_timeSetButton_clicked(){

    timeset();
}
