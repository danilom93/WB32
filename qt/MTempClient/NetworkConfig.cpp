#include "NetworkConfig.h"
#include "ui_NetworkConfig.h"

NetworkConfig::NetworkConfig(QWidget *parent) : QDialog(parent), ui(new Ui::NetworkConfig){

    ui->setupUi(this);

    this->setWindowTitle("Configura Rete");
    this->setWindowIcon(QIcon(":/ico/img/Settings-52.png"));

    QRegExp passRx("[0-9a-zA-Z]+");
    QRegExp portRx("[0-9]+");
    QRegExp addrRx("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");

    QRegExpValidator * passValidator = new QRegExpValidator(passRx, this);

    QRegExpValidator * portValidator = new QRegExpValidator(portRx, this);

    QRegExpValidator * addrValidator = new QRegExpValidator(addrRx, this);

    ui->password1LineEdit->setValidator(passValidator);
    ui->password2LineEdit->setValidator(passValidator);

    ui->boardPortLineEdit->setValidator(portValidator);

    ui->boardIPLineEdit->setValidator(addrValidator);

    ui->netNameLineEdit->setMaxLength(_MTEMP_SSID_LENGTH - 1);

    ui->netKeyLineEdit->setMaxLength(_MTEMP_SSID_KEY_LENGTH - 1);

    ui->usernameLineEdit->setMaxLength(_MTEMP_USERNAME_LENGTH - 1);

    ui->boardPortLineEdit->setMaxLength(5);

    ui->password1LineEdit->setMaxLength(_MTEMP_USER_KEY_LENGTH - 1);
    ui->password2LineEdit->setMaxLength(_MTEMP_USER_KEY_LENGTH - 1);

    m_loader = new Loader(this->windowTitle(), this);
    m_loader->hide();
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

void NetworkConfig::on_clearButton_clicked(){

    clear();
}

void NetworkConfig::on_abortButton_clicked(){

    this->close();
}

void NetworkConfig::on_configureButton_clicked(){

    QHostAddress tester;

    if(!tester.setAddress(m_boardIP)){
        QMessageBox::critical(this,
                              "Errore",
                              QString("Indirizzo IP non valido"));
        clear();
        return;
    }

    m_client = new MClient(this);

    m_client->setAddress("192.168.4.1");
    m_client->setPort(8000);

    m_client->connectToHost();
    connect(m_client, SIGNAL(connected()), this, SLOT(notifyConnected()), Qt::UniqueConnection);
    connect(m_client, SIGNAL(disconnected()), this, SLOT(notifydisconnected()), Qt::UniqueConnection);
    connect(m_client, SIGNAL(error()), this, SLOT(notifyError()), Qt::UniqueConnection);
    this->setEnabled(false);
    m_loader->show();
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

void NetworkConfig::notifyConnected(){

    m_loader->setMessage("Connesso alla centralina");
}
