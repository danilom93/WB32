#include "MClient.h"

MClient::MClient(QObject *parent) : QObject(parent), m_sock(NULL), m_addr(), m_port(0){
    /*  nulla da commentare                                                                         */
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
    /*  se la socket non è allocata                                                                 */
    if(!m_sock){
        /*  alloco la socket                                                                        */
        m_sock = new QTcpSocket(this);
    }else{
        /*  altrimenti la chiudo                                                                    */
        m_sock->close();
    }
    /*  verifico che l'indirizzo sia valido                                                         */
    hostAddr = QHostInfo::fromName(m_addr);
    /*  se ci sono stati errori                                                                     */
    if(hostAddr.error() == QHostInfo::HostNotFound ||
       hostAddr.error() == QHostInfo::UnknownError ){
        /*  ritorno false                                                                           */
        return false;
    }
    /*  provo a connettermi                                                                         */
    /*  connetto i segnali della socket                                                             */
    QObject::connect(m_sock, SIGNAL(connected())   , this, SLOT(connectedBouncer())  , Qt::UniqueConnection);
    QObject::connect(m_sock, SIGNAL(disconnected()), this, SLOT(diconnectedBouncer()), Qt::UniqueConnection);
    return true;
}

bool MClient::disconnectFromHost(){


    return true;
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
    /*  disconnetto i segnali della socket                                                          */
    QObject::disconnect(m_sock, SIGNAL(connected())   , this, SLOT(connectedBouncer())  );
    /*  emetto il segnale                                                                           */
    emit connected();
}

void MClient::diconnectedBouncer(){
    /*  disconnetto i segnali della socket                                                          */
    QObject::disconnect(m_sock, SIGNAL(disconnected()), this, SLOT(diconnectedBouncer()));
    /*  emetto il segnale                                                                           */
    emit disconnected();
}


