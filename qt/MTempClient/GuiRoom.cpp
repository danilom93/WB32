#include "GuiRoom.h"
#include <QDebug>

#define COLGRN "background-color: #99ff66"
#define COLRED "background-color: #ff8080"
#define COLBLU "background-color: #80dfff"
#define DEFCOL ""

GuiRoom::GuiRoom(QObject *parent) : QObject(parent){


}

void GuiRoom::init(const Room::RoomNumber room, QGroupBox *container, QLineEdit *temperature, QLineEdit *status, QPushButton *forceOnBtn, QPushButton *forceOffBtn, QPushButton *setAutoBtn, QPushButton *updateBtn, QPushButton *configBtn){

    m_room        = room;
    m_container   = container;
    m_temperature = temperature;
    m_status      = status;
    m_forceOnBtn  = forceOnBtn;
    m_forceOffBtn = forceOffBtn;
    m_setAutoBtn  = setAutoBtn;
    m_updateBtn   = updateBtn;
    m_configBtn   = configBtn;

    connect(m_forceOnBtn , SIGNAL(clicked()), this, SLOT(raiseForceOn()) );
    connect(m_forceOffBtn, SIGNAL(clicked()), this, SLOT(raiseForceOff()));
    connect(m_setAutoBtn , SIGNAL(clicked()), this, SLOT(raiseAuto())    );
    connect(m_updateBtn  , SIGNAL(clicked()), this, SLOT(raiseUpdate())  );
    connect(m_configBtn  , SIGNAL(clicked()), this, SLOT(raiseConfig())  );
}

void GuiRoom::setRoomName(const QString &name){

    m_container->setTitle(name);
}

QString GuiRoom::roomName() const{

    return m_container->title();
}

void GuiRoom::setTemperature(const quint32 temp){

    m_temperature->setText(QString::number(temp));
}

quint32 GuiRoom::temperature() const{

    return m_temperature->text().toUInt();
}

void GuiRoom::setStatus(const GuiRoom::RoomState stat){

    switch (stat) {
        case On:
            m_status->setText("Acceso");
            break;
        case Off:
            m_status->setText("Spento");
            break;
        default:

            break;
    }
}

GuiRoom::RoomState GuiRoom::status() const{

    if(m_status->text() == "Acceso"){
        return On;
    }
    return Off;
}

void GuiRoom::setRoomMode(const GuiRoom::RoomMode mode){

    switch (mode){

    case Auto:
        m_setAutoBtn->setStyleSheet(COLBLU);
        m_forceOnBtn->setStyleSheet(DEFCOL);
        m_forceOffBtn->setStyleSheet(DEFCOL);
        break;
    case ForcedOn:
        m_setAutoBtn->setStyleSheet(DEFCOL);
        m_forceOnBtn->setStyleSheet(COLGRN);
        m_forceOffBtn->setStyleSheet(DEFCOL);
        break;
    case ForcedOff:
        m_setAutoBtn->setStyleSheet(DEFCOL);
        m_forceOnBtn->setStyleSheet(DEFCOL);
        m_forceOffBtn->setStyleSheet(COLRED);
        break;
    default:
        break;
    }
}

GuiRoom::RoomMode GuiRoom::roomMode() const{

    if(!m_setAutoBtn->styleSheet().isEmpty()){
        return Auto;
    }
    if(!m_forceOnBtn->styleSheet().isEmpty()){
        return ForcedOn;
    }
    if(!m_forceOffBtn->styleSheet().isEmpty()){
        return ForcedOff;
    }
}

void GuiRoom::update(const QString &str){

}

void GuiRoom::enable(const bool all){

    m_container->setEnabled(true);
    m_temperature->setEnabled(true);
    m_status->setEnabled(true);
    m_forceOnBtn->setEnabled(true);
    m_forceOffBtn->setEnabled(true);
    m_setAutoBtn->setEnabled(true);
    m_updateBtn->setEnabled(true);
    if(all){
        m_configBtn->setEnabled(true);
    }
}

void GuiRoom::disable(const bool all){

    m_container->setEnabled(false);
    m_temperature->setEnabled(false);
    m_status->setEnabled(false);
    m_forceOnBtn->setEnabled(false);
    m_forceOffBtn->setEnabled(false);
    m_setAutoBtn->setEnabled(false);
    m_updateBtn->setEnabled(false);
    if(all){
        m_configBtn->setEnabled(false);
    }

}

void GuiRoom::raiseUpdate(){
    qDebug() << "raiseUpdate()";
    emit updateRequest(m_room);
}

void GuiRoom::raiseForceOn(){
    qDebug() << "raiseForceOn()";
    emit forceOnRequest(m_room, "test");
}

void GuiRoom::raiseForceOff(){
    qDebug() << "raiseForceOff()";
    emit forceOffRequest(m_room, "test");
}

void GuiRoom::raiseAuto(){
    qDebug() << "raiseAuto()";
    emit forceAutoRequest(m_room, "test");

}

void GuiRoom::raiseConfig(){
    qDebug() << "raiseConfig()";
    emit configRequest(m_room, "test");
}
