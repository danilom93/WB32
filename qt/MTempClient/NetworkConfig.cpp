#include "NetworkConfig.h"
#include "ui_NetworkConfig.h"

NetworkConfig::NetworkConfig(QWidget *parent) : QDialog(parent), ui(new Ui::NetworkConfig){
    /*  espressione regolare per la password                                                        */
    QRegExp passRx("[0-9a-zA-Z]+");
    /*  espressione regolare per la porta                                                           */
    QRegExp portRx("[0-9]+");
    /*  espressione regolare per l'indirizzo ip                                                     */
    QRegExp addrRx("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
    /*  validator per password                                                                      */
    QRegExpValidator * passValidator = new QRegExpValidator(passRx, this);
    /*  validator per porta                                                                         */
    QRegExpValidator * portValidator = new QRegExpValidator(portRx, this);
    /*  validator per ip                                                                            */
    QRegExpValidator * addrValidator = new QRegExpValidator(addrRx, this);
    /*  completamento interfaccia                                                                   */
    ui->setupUi(this);
    /*  imposto il titolo                                                                           */
    this->setWindowTitle("Configura Rete");
    /*  imposto le icone                                                                            */
    this->setWindowIcon(QIcon(":/ico/img/Settings-52.png"));
    /*  imposto il validator per la password1                                                       */
    ui->password1LineEdit->setValidator(passValidator);
    /*  imposto il validator per la password2                                                       */
    ui->password2LineEdit->setValidator(passValidator);
    /*  imposto il validator per la porta                                                           */
    ui->boardPortLineEdit->setValidator(portValidator);
    /*  imposto il validatore per l'ip                                                              */
    ui->boardIPLineEdit->setValidator(addrValidator);
    /*  fisso la lunghezza massima per il nome della rete                                           */
    ui->netNameLineEdit->setMaxLength(_MTEMP_SSID_LENGTH - 1);
    /*  fisso la lunghezza massima per la chiave di rete                                            */
    ui->netKeyLineEdit->setMaxLength(_MTEMP_SSID_KEY_LENGTH - 1);
    /*  fisso la lunghezza massima per l'username                                                   */
    ui->usernameLineEdit->setMaxLength(_MTEMP_USERNAME_LENGTH - 1);
    /*  fisso la lunghezza massima per la porta                                                     */
    ui->boardPortLineEdit->setMaxLength(5);
    /*  fisso la lunghezza massima per la password1                                                 */
    ui->password1LineEdit->setMaxLength(_MTEMP_USER_KEY_LENGTH - 1);
    /*  fisso la lunghezza massima per la password2                                                 */
    ui->password2LineEdit->setMaxLength(_MTEMP_USER_KEY_LENGTH - 1);
    /*  creo il loader per l'attesa                                                                 */
    m_loader = new Loader(this->windowTitle(), this);
    /*  nascondo il loader                                                                          */
    m_loader->hide();
    /*  creo il client                                                                              */
    m_client = new MClient(this);
    /*  connetto i segnali                                                                          */
    connect(m_client, SIGNAL(connected())   ,
            this, SLOT(notifyConnected())   );
    /*  connetto i segnali                                                                          */
    connect(m_client, SIGNAL(disconnected()),
            this, SLOT(notifyDisconnected()));
    /*  connetto i segnali                                                                          */
    connect(m_client, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(notifyError(QAbstractSocket::SocketError)));
    /*  connetto i segnali                                                                          */
    connect(m_client, SIGNAL(tokenReceived()),
            this, SLOT(rxHandler()));
    /*  connetto i segnali                                                                          */
    connect(m_client, SIGNAL(dataSended()),
            this, SLOT(txHandler()));
    /*  imposto lo stato                                                                            */
    m_state = NotConnected;
}

NetworkConfig::~NetworkConfig(){

    delete ui;
}

void NetworkConfig::on_netKeyShowChecbox_clicked(bool checked){

    if(checked){
        ui->netKeyLineEdit->setEchoMode(QLineEdit::Normal);
    }else{
        ui->netKeyLineEdit->setEchoMode(QLineEdit::Password);
    }
}

void NetworkConfig::on_netNameLineEdit_textChanged(const QString &arg1){


    if(arg1.contains(_MTEMP_CONF_START) || arg1.contains(_MTEMP_CONF_END)){
        QMessageBox::critical(this,
                              "Errore",
                              QString("Il nome della rete non può contenere ") +
                              QString(_MTEMP_CONF_START) + QString(" o ")      +
                              QString(_MTEMP_CONF_END));
        ui->netNameLineEdit->clear();
        return;
    }
    m_networkName = arg1;
    checkAll();
}


void NetworkConfig::on_netKeyLineEdit_textChanged(const QString &arg1){

    if(arg1.contains(_MTEMP_CONF_START) || arg1.contains(_MTEMP_CONF_END)){
        QMessageBox::critical(this,
                              "Errore",
                              QString("La chiave di rete non può contenere ")  +
                              QString(_MTEMP_CONF_START) + QString(" o ")      +
                              QString(_MTEMP_CONF_END));
        ui->netKeyLineEdit->clear();
        return;
    }
    m_networkKey = arg1;
    checkAll();
}

void NetworkConfig::on_boardIPLineEdit_textChanged(const QString &arg1){

    m_boardIP = arg1;
    checkAll();
}

void NetworkConfig::on_usernameLineEdit_textChanged(const QString &arg1){

    if(arg1.contains(_MTEMP_CONF_START) || arg1.contains(_MTEMP_CONF_END)){
        QMessageBox::critical(this,
                              "Errore",
                              QString("Il nome utente non può contenere ") +
                              QString(_MTEMP_CONF_START) + QString(" o ")  +
                              QString(_MTEMP_CONF_END));
        ui->usernameLineEdit->clear();
        return;
    }
    m_username = arg1;
    checkAll();
}

void NetworkConfig::on_password1LineEdit_textChanged(const QString &arg1){

    if(arg1.contains(_MTEMP_CONF_START) || arg1.contains(_MTEMP_CONF_END)){
        QMessageBox::critical(this,
                              "Errore",
                              QString("La password non può contenere ")    +
                              QString(_MTEMP_CONF_START) + QString(" o ")  +
                              QString(_MTEMP_CONF_END));
        ui->password1LineEdit->clear();
        return;
    }
    m_password1 = arg1;
    checkAll();
}

void NetworkConfig::on_password2LineEdit_textChanged(const QString &arg1){

    if(arg1.contains(_MTEMP_CONF_START) || arg1.contains(_MTEMP_CONF_END)){
        QMessageBox::critical(this,
                              "Errore",
                              QString("La password non può contenere ")    +
                              QString(_MTEMP_CONF_START) + QString(" o ")  +
                              QString(_MTEMP_CONF_END));
        ui->password2LineEdit->clear();
        return;
    }
    m_password2 = arg1;
    checkAll();
}

void NetworkConfig::on_boardPortLineEdit_textChanged(const QString &arg1){

    if(arg1.toUInt() > 65535){
        QMessageBox::critical(this,
                              "Errore",
                              QString("La porta non può essere maggiore di 65535"));
        ui->boardPortLineEdit->clear();
        return;
    }

    m_boardPort = arg1.toUInt();
    checkAll();

}

void NetworkConfig::on_clearButton_clicked(){

    clear();
}

void NetworkConfig::on_abortButton_clicked(){

    this->close();
}

void NetworkConfig::on_configureButton_clicked(){

    QHostAddress tester;
    /*  verifico che l'indirizzo sia ok                                                             */
    if(!tester.setAddress(m_boardIP)){
        /*  se non è così informo l'utente                                                          */
        QMessageBox::critical(this,
                              "Errore",
                              QString("Indirizzo IP non valido"));
        /*  cancello il form                                                                        */
        clear();
        /*  ritorno                                                                                 */
        return;
    }
    /*  se sono in qualsiasi altro stato all'infuori di notConnected                                */
    if(m_state != NotConnected){
        /*  informo l'utente                                                                        */
        QMessageBox::critical(this,
                              "Errore",
                              QString("La vecchia connessione è ancora aperta"));
        /*  e ritorno                                                                               */
        return;
    }
    /*  imposto l'indirizzo di connessione                                                          */
    m_client->setAddress("192.168.4.1");
    /*  imposto la porta                                                                            */
    m_client->setPort(8000);
    /*  provo a connettermi                                                                         */
    m_client->connectToHost();
    /*  mostro il loader                                                                            */
    m_loader->show();
    /*  imposto il messaggio                                                                        */
    m_loader->setMessage("Provo a connettermi alla centralina");
}

void NetworkConfig::notifyConnected(){
    QString str;
    /*  imposto il messaggio nel loader                                                             */
    m_loader->setMessage("Connesso alla centralina");
    /*  imposto lo stato                                                                            */
    m_state = Connected;
    /*  costruisco la stringa di configurazione                                                     */
    str += _MTEMP_CONF_START;
    str += _MTEMP_SEP;
    str += m_networkName;
    str += _MTEMP_SEP;
    str += m_networkKey;
    str += _MTEMP_SEP;
    str += m_boardIP;
    str += _MTEMP_SEP;
    str += QString::number(m_boardPort);
    str += _MTEMP_SEP;
    str += m_username;
    str += _MTEMP_SEP;
    str += m_password1;
    str += _MTEMP_SEP;
    str += _MTEMP_CONF_END;
    /*  imposto lo stato                                                                            */
    m_state = SendConfiguration;
    /*  setto la stringa per l'ok                                                                   */
    m_client->waitFor(_MTEMP_CONF_OK);
    /*  mando la configurazione                                                                     */
    m_client->write(str);

}

void NetworkConfig::notifyError(QAbstractSocket::SocketError){

    QMessageBox::critical(this, "Errore", m_client->lastError());
    clear();
}

void NetworkConfig::notifyDisconnected(){

    m_loader->setMessage("Disconnesso dalla centralina");
    m_loader->hide();
    this->close();
}

void NetworkConfig::rxHandler(){

    if(m_state == WaitAnswer){
        QMessageBox::information(this, this->windowTitle(), "Centralina configurarata correttamente");
        m_client->disconnectFromHost();
    }
}

void NetworkConfig::txHandler(){

    if(m_state == SendConfiguration){
        m_state = WaitAnswer;
    }

}


void NetworkConfig::clear(){

    ui->netNameLineEdit->clear();
    ui->netKeyLineEdit->clear();
    ui->boardIPLineEdit->clear();
    ui->boardPortLineEdit->clear();
    ui->usernameLineEdit->clear();
    ui->password1LineEdit->clear();
    ui->password2LineEdit->clear();
}

void NetworkConfig::checkAll(){

    QHostAddress tester;

    if(!m_networkName.isEmpty()     &&
       !m_networkKey.isEmpty()      &&
       tester.setAddress(m_boardIP) &&
       (m_boardPort != 0)           &&
       !m_username.isEmpty()        &&
       !m_password1.isEmpty()       &&
       (m_password1 == m_password2)){
        ui->configureButton->setEnabled(true);
    }else{
        ui->configureButton->setEnabled(false);
    }
}



