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
    
    AString dataRcv;
    
    if(!m_flag){
        
        return false;
    }
    
    msg("Configurazione\nRete...");
    
    if(prepareAp(_MTEMP_SSID_AP, _MTEMP_PWD_AP, _MTEMP_PORT_AP)){

        msg("In attesa di\nConnessioni...", 0);

        while(1){
            
            if(m_wifi->waitForData(dataRcv)){
                
                if(dataRcv.contains(_MTEMP_CONF)){
    
                    msg("Dati ricevuti,\nSalvataggio...");
                    
                    if(saveNetworkConfig(dataRcv)){
                    
                        msg("Salvataggio ok!", 0);
                        
                        if(m_wifi->send(_MTEMP_BOARD_OK)){
                            
                            msg("Avvio tra\n1 secondo...");
                            return true;
                        }
                    }else{
                        
                        m_wifi->send(_MTEMP_BOARD_FAIL);
                        msg("Errore\nConfigurazione!");
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
            
            /* joinNetwork da direttamente l'output                             */
        if(loadAll()){
            
            msg("Errore\nCaricamento", 0);
            while(1);
        }
            m_wifi->prepareForReceive();
            
            while(1){
                
                if(m_wifi->waitForData(currentCmd, 0)){

                    commandExec(currentCmd);
                }else{

                    programsManager();
                }
            }
    }else{
        /*  joinNetwork da direttamente l'output                                */
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
    
    bool flg = false;
    
    if(!m_flag){
        
        return false;
    }
    AStringList *list = NULL;
    
    list = data.split(_MTEMP_SEP);
    
    if(list && data.good()){
        /*
         *  FORMATO STRINGA CONF
         *  (CLIENT)        SSID*KEY*IP*PORT*USER*PASSWORD*[CONF]
         */
        flg = (m_memory->write(_MTEMP_SSID_ADDRESS         , list->at(0)) &&
               m_memory->write(_MTEMP_SSID_KEY_ADDRESS     , list->at(1)) &&
               m_memory->write(_MTEMP_MASTER_IP_ADDRESS    , list->at(2)) &&
               m_memory->write(_MTEMP_MASTER_PORT_ADDRESS  , list->at(3)) &&
               m_memory->write(_MTEMP_USERNAME_ADDRESS     , list->at(4)) &&
               m_memory->write(_MTEMP_USER_KEY_ADDRESS     , list->at(5)));
         
        
        delete list;
        
        return flg;
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
    
    msg("Carico i\nParametri...");
    
    if( !m_memory->read(_MTEMP_SSID_ADDRESS,         ssid) ||
        !m_memory->read(_MTEMP_SSID_KEY_ADDRESS,     pwd)  ||
        !m_memory->read(_MTEMP_MASTER_PORT_ADDRESS,  port) ||
        !m_memory->read(_MTEMP_MASTER_IP_ADDRESS,    ip)   ){
        
        return false;
    }

    msg("Parametri\nCaricati...");
    
    /*  errore 1                                                                */
    if(m_wifi->isOk()){    
        msg("Connessione\nIn corso...");
        /*  errore 2                                                            */
        if(m_wifi->setMode(AESP8266::StationMode)){
            /*  errore 3                                                        */
            if(m_wifi->setEcho(false)){
                /*  errore 4                                                    */
                if(m_wifi->joinAP(ssid, pwd)){
                    /*  errore 5                                                */
                    if(m_wifi->setDhcp(false)){
                        /*  errore 6                                            */
                        if(m_wifi->setIp(ip)){
                            /*  errore 7                                        */
                            if(m_wifi->setMultipleConnections(true)){
                                /*  errore 8                                    */
                                if(m_wifi->openServer(static_cast<uint16>(port.toInt32(flag)))){
                                        
                                        msg("Connesso ed\nIn ascolto...");
                                        return true;
                                }else{
                                    msg("Errore Modulo\n[8]");
                                }
                            }else{
                                msg("Errore Modulo\n[7]");
                            }
                        }else{
                            msg("Errore Modulo\n[6]");
                        }
                    }else{
                        msg("Errore Modulo\n[5]");
                    }
                }else{
                    msg("Errore Modulo\n[4]");
                }
            }else{
                msg("Errore Modulo\n[3]");
            }
        }else{
            msg("Errore Modulo\n[2]");
        }
    }else{
        msg("Errore Modulo\n[1]");
    }
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
    
    msg("Carico i\nProgrammi...");
    
    for(uint8 i = 0; i <_MTEMP_ROOM_VEC_SIZE; i++){
    
        m_rooms[i].setRoomNumber(static_cast<Room::RoomNumber>(i));
        m_rooms[i].loadRoom();
        
        for(uint8 j = 0; j < _MTEMP_WEEKPROGRAM_VEC_SIZE; j++){
          
            m_rooms[i].loadProgram(static_cast<ADateTime::Weekdays>(j+1));
        }
    }     
    
    msg("Programmi\nCaricati...");
    
    return m_memory->read(_MTEMP_USERNAME_ADDRESS, m_username) && m_memory->read(_MTEMP_USER_KEY_ADDRESS, m_password);
}

void AFramework::MTempMaster::commandExec(const AString &cmd) const{
    
    AStringList *   list;
    AString         str;
    ADateTime       time;
    bool            flag = false;
   
    
    list = cmd.split(_MTEMP_SEP);
    
    if(list && cmd.good()){
        
        if(list->at(0) == m_username && list->at(1) == m_password){
            
            str = list->at(list->size() - 1);
            
            if(str == _MTEMP_TIMESET){
                //*  (CLIENT)        username*password*AA*MM*GG*WD*HH*MM*SS*[TIMESET]
                if(time.setYear(list->at(2).toInt32(flag)) && flag){
                    
                    if(time.setMonth(static_cast<ADateTime::Months>(list->at(3).toInt32(flag))) && flag){
                        
                        if(time.setDayOfMonth(list->at(4).toInt32(flag)) && flag){
                            
                            if(time.setWeekday(static_cast<ADateTime::Weekdays>(list->at(5).toInt32(flag))) && flag){
                                
                                if(time.setHours(list->at(6).toInt32(flag)) && flag){
                                    
                                    if(time.setMinutes(list->at(7).toInt32(flag)) && flag){
                                        
                                        if(time.setSeconds(list->at(8).toInt32(flag)) && flag){
                                            
                                            if(m_clk->setTime(time)){
                                                
                                                if(m_wifi->send(_MTEMP_BOARD_OK)){
                                                    
                                                    str.clear();
                                                    str = m_clk->currentTime().timeToString();
                                                    str.prepend("Ora settata\n");
                                                    msg(str);
                                                    delete list;
                                                    return;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

            }else if(str == _MTEMP_TIMEGET){
                
                //*  (CLIENT)        username*password*[TIMEGET]
                //*  (SERVER)        (AA*MM*GG*WD*HH*MM*SS*[OK] || [FAIL] || [ERROR])
                
                if(m_clk->isGood()){
                    
                    time = m_clk->currentTime();
                    str += AString(time.year() - 2000);
                    str += AString(static_cast<uint8>(time.month()));
                    str += AString(time.dayOfMonth());
                    str += AString(static_cast<uint8>(time.Weekday()));
                    str += AString(time.hours());
                    str += AString(time.minutes());
                    str += AString(time.seconds());
                    str += _MTEMP_BOARD_OK;
                    m_wifi->send(str);
                }else{
                    
                    m_wifi->send(_MTEMP_BOARD_FAIL);
                    msg("Errore...\nOrologio");
                }
                
            }else{
                
            }
        }else{
            
            m_wifi->send(_MTEMP_BOARD_ERROR);
        }
    }
    if(list){
        
        delete list;
        msg("Errore\nCmd Handler");
    }
    return;
}

void AFramework::MTempMaster::msg(const QString & s, const uint32 ms) const{
    m_lcd->clear();
    if(s.isEmpty()){
        m_lcd->write("NULL POINTER");
        while(1);
    }else{
        m_lcd->write(s.c_str());    
    }
    System::delay(ms);
}

void AFramework::MTempMaster::msg(const char * s, const uint32 ms) const{
    m_lcd->clear();
    if(!s){
        m_lcd->write("NULL POINTER");
        while(1);
    }else{
        m_lcd->write(s);    
    }
    System::delay(ms);
}
