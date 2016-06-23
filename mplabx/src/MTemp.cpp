#include "MTemp.h"

#define _MTEMP_SSID_AP              "MTemp"
#define _MTEMP_PWD_AP               "802.15.4"
#define _MTEMP_PORT_AP              8000
#define _MTEMP_ROOM_DEFAULT_NAME    "Room"
#define _MTEMP_ROOM_DEFAULT_PROGRAM "*00*00*23*59*25*N"

#define __DEBUG_MODE

#ifdef __DEBUG_MODE

#include "AUARTDriver.h"

#endif

AFramework::MTempMaster::MTempMaster(AXbee * xbee, APCF8563 *clk, A24LC512 *mem, AESP8266 *wifi, ALcd *lcd, volatile AHardwarePort *port){
    
    m_flag = false;
    if(xbee && clk && mem && wifi && lcd && port){
        
        m_xbee = xbee;
        m_clk = clk;
        m_memory = mem;
        m_wifi = wifi;
        m_lcd = lcd;
        m_flag = true;
        m_port = port;
        Room::setEEPROM(m_memory);
        Room::setPORT(m_port);
    }
}

bool AFramework::MTempMaster::networkConfig() const{
    
    bool flag = true;
    AString dataRcv;
    
    if(!m_flag){
        
        return false;
    }
    m_lcd->write("Configurazione\nRete...");
    
    if(prepareAp(_MTEMP_SSID_AP, _MTEMP_PWD_AP, _MTEMP_PORT_AP)){
        
        #ifdef __DEBUG_MODE
            
            UART2.writeln("ESP IN ATTESA DI CONNESSIONI");
        #endif
        m_lcd->clear();
        m_lcd->write("In attesa di\nConnessioni...");
        while(flag){
            
            if(m_wifi->waitForData(dataRcv)){
                
                if(dataRcv.contains(_MTEMP_CONF)){
                    #ifdef __DEBUG_MODE
            
                        UART2.writeln("DATI RICEVUTI : ");
                        UART2.writeln(dataRcv.c_str());
                    #endif
                    if(saveNetworkConfig(dataRcv)){
                        
                        if(m_wifi->send(_MTEMP_BOARD_OK)){
                            
                            #ifdef __DEBUG_MODE
            
                                UART2.writeln("Ok inviato");
                            #endif
                            
                            m_lcd->clear();
                            m_lcd->write("Configurazione\nSalvata");
                            System::delay(1000);
                            return true;
                        }
                    }else{
                        
                        m_wifi->send(_MTEMP_BOARD_FAIL);
                        m_lcd->clear();
                        m_lcd->write("Errore\nConfigurazione");
                        System::delay(1000);
                        return false;
                    }
                }
            }
        }          
    }
}

bool AFramework::MTempMaster::run(){
    
    AString currentCmd;
    if(!m_flag){
        
        return false;
    }
    if(joinNetwork()){
        
        #ifdef __DEBUG_MODE
            UART2.writeln("Connesso alla rete");
        #endif
        //if(loadAll()){
            
            m_wifi->prepareForReceive();
            while(1){
                if(m_wifi->waitForData(currentCmd, 0)){

                    commandExec(currentCmd);
                }else{

                    programsManager();
                }
            }
        //}
    }else{
        
        m_lcd->clear();
        m_lcd->write("ERRORE\nJOIN");
        while(1);
    }
}

bool AFramework::MTempMaster::defaultProgram(){
    
    if(!m_flag){
        
        return false;
    }
    
    for(uint8 i = 0; i <_MTEMP_ROOM_VEC_SIZE; i++){
        
        AString str;
        
        str += _MTEMP_ROOM_DEFAULT_NAME;
        str += static_cast<char>(i + 0x30);
        
        m_rooms[i].setRoomNumber(static_cast<Room::RoomNumber>(i));
        m_rooms[i].setRoomName(str);
        m_rooms[i].setSensorAddress(i);
        m_rooms[i].setRelayOut(1 << i);
        m_rooms[i].saveRoom();
        
        for(uint8 j = 0; j < _MTEMP_WEEKPROGRAM_VEC_SIZE; j++){
            
            AString prg = _MTEMP_ROOM_DEFAULT_PROGRAM;
            
            prg.prepend(static_cast<char>(j + 0x31));
            
            m_rooms[i].setProgram(static_cast<ADateTime::Weekdays>(j + 1), prg);
            
            m_rooms[i].saveProgram(static_cast<ADateTime::Weekdays>(j + 1));
        }
    }   
    return true;
}

bool AFramework::MTempMaster::saveNetworkConfig(const AString &data) const{
    
    if(!m_flag){
        
        return false;
    }
    AStringList *list = NULL;
    
    list = data.split(_MTEMP_SEP);
    
    if(list && data.good()){
        
        #ifdef __DEBUG_MODE
            
            for(int i = 0; i < list->size(); i++){
                UART2.writeln(list->at(i).c_str());
            }
        #endif
        /*
         *  FORMATO STRINGA CONF
         *  (CLIENT)        SSID*KEY*IP*PORT*USER*PASSWORD*[CONF]
         */
        if( m_memory->write(_MTEMP_SSID_ADDRESS         , list->at(0)) &&
            m_memory->write(_MTEMP_SSID_KEY_ADDRESS     , list->at(1)) &&
            m_memory->write(_MTEMP_MASTER_IP_ADDRESS    , list->at(2)) &&
            m_memory->write(_MTEMP_MASTER_PORT_ADDRESS  , list->at(3)) &&
            m_memory->write(_MTEMP_USERNAME_ADDRESS     , list->at(4)) &&
            m_memory->write(_MTEMP_USER_KEY_ADDRESS     , list->at(5))){
            
            #ifdef __DEBUG_MODE
            
                UART2.writeln("DATI SALVATI");
            #endif
        }
        
        delete list;
        return true;
    }
    
    return false;
}

bool AFramework::MTempMaster::prepareAp(const AString &ssid, const AString &pwd, const uint16 port) const{
    
    if(m_flag){
        if(m_wifi->isOk()){
            #ifdef __DEBUG_MODE
                UART2.writeln("ESP OK");
            #endif
            if(m_wifi->setMode(AESP8266::APMode)){
                #ifdef __DEBUG_MODE
                    UART2.writeln("ESP IN AP MODE");
                #endif
                if(m_wifi->configureAP(ssid, pwd)){  
                        #ifdef __DEBUG_MODE
                            UART2.writeln("ESP AP CONFIGURATO");
                        #endif
                        if(m_wifi->setEcho(false)){
                            #ifdef __DEBUG_MODE
                                UART2.writeln("ESP ECHO OFF");
                            #endif
                            if(m_wifi->setMultipleConnections(true)){
                                #ifdef __DEBUG_MODE
                                    UART2.writeln("ESP MUX OK");
                                #endif
                            if(m_wifi->openServer(port)){
                                #ifdef __DEBUG_MODE
                                    UART2.writeln("ESP SERVER IN ASCOLTO");
                                #endif
                                if(m_wifi->prepareForReceive()){
                                    return true;    
                                }    
                            }
                        }
                    }
                    
                }
            }
        }
    }
    #ifdef __DEBUG_MODE
            
        UART2.writeln("ERRORE IN prepareAP!!!!!!!!!!!!!!!!");
    #endif
    return false;
}

void AFramework::MTempMaster::checkPrograms(){
    
    if(!m_flag){
        
        return;
    }
    memset(m_rooms, 0x00, _MTEMP_ROOM_VEC_SIZE * sizeof(Room));
    
    UART2.writeln("Inizio verifica");
    
    for(uint8 i = 0; i <_MTEMP_ROOM_VEC_SIZE; i++){
    
        m_rooms[i].setRoomNumber(static_cast<Room::RoomNumber>(i));
        m_rooms[i].loadRoom();
        
        UART2.writeln(m_rooms[i].toString().c_str());
        
        for(uint8 j = 0; j < _MTEMP_WEEKPROGRAM_VEC_SIZE; j++){
          
            m_rooms[i].loadProgram(static_cast<ADateTime::Weekdays>(j+1));
    
            UART2.writeln(m_rooms[i].program(static_cast<ADateTime::Weekdays>(j+1)).toString().c_str());
        }
    }     
    return;
}

bool AFramework::MTempMaster::joinNetwork() const{
    
    AString ssid;
    AString pwd;
    AString ip;
    AString port;
    bool    flag = false;
    
    if(!m_flag){
        
        return false;
    }
    if( !m_memory->read(_MTEMP_SSID_ADDRESS,         ssid) ||
        !m_memory->read(_MTEMP_SSID_KEY_ADDRESS,     pwd)  ||
        !m_memory->read(_MTEMP_MASTER_PORT_ADDRESS,  port) ||
        !m_memory->read(_MTEMP_MASTER_IP_ADDRESS,    ip)   ){
        
        return false;
    }
    #ifdef __DEBUG_MODE
        UART2.writeln(ssid.c_str());
        UART2.writeln(pwd.c_str());
        UART2.writeln(ip.c_str());
        UART2.writeln(port.c_str());
    #endif
    
    if(m_wifi->isOk()){
        
        m_lcd->clear();
        m_lcd->write("Connessione\nIn corso...");
        
        if(m_wifi->setMode(AESP8266::StationMode)){
            
            if(m_wifi->setEcho(false)){
                
                if(m_wifi->joinAP(ssid, pwd)){
                    
                    if(m_wifi->setDhcp(false)){
                        
                        if(m_wifi->setIp(ip)){
                            
                            if(m_wifi->setMultipleConnections(true)){
                                
                                if(m_wifi->openServer(static_cast<uint16>(port.toInt32(flag)))){
                                    
                                    if(flag){
                                        
                                        m_lcd->clear();
                                        m_lcd->write("Server\nIn Ascolto...");
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    m_lcd->clear();
    m_lcd->write("Errore WIFI");
    return false;
}

bool AFramework::MTempMaster::programsManager() const{                                                //da fare
    
    ADateTime currentClk;
    if(!m_flag){
        
        return false;
    }
    if(m_clk->isGood()){
        
        currentClk = m_clk->currentTime();
        
        for(uint8 i=0; i < _MTEMP_ROOM_VEC_SIZE; i++){
            
            if(m_rooms[i].program(currentClk.Weekday()).startHours() == currentClk.hours()){
                
            }
        }
    }else{
        
        m_lcd->clear();
        m_lcd->write("Errore ora");
        System::delay(1000);
    }
    return false;
}

bool AFramework::MTempMaster::loadAll(){
    
    if(!m_flag){
        
        return false;
    }
    
    for(uint8 i = 0; i <_MTEMP_ROOM_VEC_SIZE; i++){
    
        m_rooms[i].setRoomNumber(static_cast<Room::RoomNumber>(i));
        m_rooms[i].loadRoom();
        
        for(uint8 j = 0; j < _MTEMP_WEEKPROGRAM_VEC_SIZE; j++){
          
            m_rooms[i].loadProgram(static_cast<ADateTime::Weekdays>(j+1));
        }
    }     
    return m_memory->read(_MTEMP_USERNAME_ADDRESS, m_username) && m_memory->read(_MTEMP_USER_KEY_ADDRESS, m_password);
}

void AFramework::MTempMaster::commandExec(const AString &cmd) const{
    
    return;
}