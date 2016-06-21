#include "MClient.h"

MClient::MClient(QObject *parent) : QObject(parent), m_sock(NULL), m_addr(), m_port(0), m_state(false), m_dataLen(0){
    /*  nulla da commentare                                                                         */
    m_sock = new QTcpSocket(this);

    connect(m_sock, SIGNAL(connected())   , this, SLOT(connectedBouncer())  );
    connect(m_sock, SIGNAL(disconnected()), this, SLOT(diconnectedBouncer()));
    connect(m_sock, SIGNAL(byte))

}

MClient::~MClient(){
    /*  se la socket è allocata                                                                     */
    if(m_sock){
        /*  la chiudo                                                                               */
        m_sock->close();
        /*  e libero la memoria                                                                     */
        delete m_sock;
    }
}

QString MClient::address() const{
    /*  nulla da commentare                                                                         */
    return m_addr;
}

quint16 MClient::port() const{
    /*  nulla da commentare                                                                         */
    return m_port;
}

bool MClient::connectToHost(){

    QHostInfo hostAddr;
    /*  chiudo la socket                                                                            */
    m_sock->close();
    /*  verifico che l'indirizzo sia valido                                                         */
    hostAddr = QHostInfo::fromName(m_addr);
    /*  se ci sono stati errori                                                                     */
    if(hostAddr.error() == QHostInfo::HostNotFound ||
       hostAddr.error() == QHostInfo::UnknownError ){
        /*  ritorno false                                                                           */
        return false;
    }
    /*  provo a connettermi                                                                         */
    m_sock->connectToHost(m_addr, m_port);
    return true;
}

bool MClient::disconnectFromHost(){
    /*  se non sono connesso                                                                        */
    if(!m_state){
        /*  ritorno false                                                                           */
        return false;
    }
    /*  mi disconnetto                                                                              */
    m_sock->disconnectFromHost();
    /*  ritorno true                                                                                */
    return true;
}

bool MClient::write(const QString &str){
    /*  se non sono connesso                                                                        */
    if(!m_state){
        /*  ritorno false                                                                           */
        return false;
    }
    /*  imposto la dimensione del dato                                                              */
    m_dataLen = str.toLocal8Bit().size();
    /*  scrivo sulla socket                                                                         */
    m_sock->write(str.toLocal8Bit());
    /*  ritorno true                                                                                */
    return true;
}

bool MClient::waitFor(const QString &str){
    /*  se non sono connesso                                                                        */
    if(!m_state){
        /*  ritorno false                                                                           */
        return false;
    }
    /*  imposto la keyword                                                                          */
    m_keyword = str;
    /*  ritorno true                                                                                */
}

QString MClient::dataReceived() const{
    /*  ritorno il buffer                                                                           */
    return m_buffer;
}

void MClient::bufferClear(){
    /*  pulisco il buffer                                                                           */
    m_buffer.clear();
}

bool MClient::setAddress(const QString &addr){
    /*  se l'indirizzo è diverso da quello precedente                                               */
    if(m_addr != addr){
        /*  cambio l'indirizzo                                                                      */
        m_addr = addr;
        /*  ed emetto il segnale                                                                    */
        emit addressChanged(addr);
        /*  ritorno true                                                                            */
        return true;
    }
    /*  altrimenti ritorno false                                                                    */
    return false;
}

bool MClient::setPort(const quint16 &port){
    /*  se la porta è diverso da quella precedente                                                  */
    if(m_port != port){
        /*  cambio la porta                                                                         */
        m_port = port;
        /*  ed emetto il segnale                                                                    */
        emit portChanged(port);
        /*  ritorno true                                                                            */
        return true;
    }
    /*  altrimenti ritorno false                                                                    */
    return false;
}

void MClient::connectedBouncer(){
    /*  imposto il flag di connessione                                                              */
    m_state = true;
    /*  emetto il segnale                                                                           */
    emit connected();
}

void MClient::diconnectedBouncer(){
    /*  imposto il flag di connessione                                                              */
    m_state = false;
    /*  emetto il segnale                                                                           */
    emit disconnected();
}


