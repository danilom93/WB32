#include "MTemp.h"
#include "MTempDefs.h"
#include "MTempCommons.h"

#define _MTEMP_SSID_AP  "MTemp"
#define _MTEMP_PWD_AP   "802.15.4"
#define _MTEMP_PORT_AP  8000

#define __DEBUG_MODE

#ifdef __DEBUG_MODE

#include "AUARTDriver.h"

#endif

AFramework::MTempMaster::MTempMaster(AXbee * xbee, APCF8563 *clk, A24LC512 *mem, AESP8266 *wifi){
    
    m_flag = false;
    if(xbee && clk && mem && wifi){
        
        m_xbee = xbee;
        m_clk = clk;
        m_memory = mem;
        m_wifi = wifi;
        m_flag = true;
    }
}

bool AFramework::MTempMaster::prepareAp(const AString &ssid, const AString &pwd, const uint16 port){
    
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

bool AFramework::MTempMaster::networkConfig(){
    
    bool flag = true;
    AString dataRcv;
    
    if(prepareAp(_MTEMP_SSID_AP, _MTEMP_PWD_AP, _MTEMP_PORT_AP)){
        
        #ifdef __DEBUG_MODE
            
            UART2.writeln("ESP IN ATTESA DI CONNESSIONI");
        #endif
        
        while(flag){
            
            if(m_wifi->waitForData(dataRcv)){
                
                if(dataRcv.contains(_MTEMP_CONF_END)){
                    #ifdef __DEBUG_MODE
            
                        UART2.writeln("DATI RICEVUTI : ");
                        UART2.writeln(dataRcv.c_str());
                    #endif
                    if(saveNetworkConfig(dataRcv)){
                        
                        if(m_wifi->send(_MTEMP_CONF_OK)){
                            
                            #ifdef __DEBUG_MODE
            
                                UART2.writeln("CONF OK INVIATA");
                            #endif
                        }
                    return true;
                    }
                }
            }
        }       
        
    }
}

bool AFramework::MTempMaster::saveNetworkConfig(const AString &data){
    
    AStringList *list = NULL;
    
    list = data.split(_MTEMP_SEP);
    
    if(list && list->good()){
        
        #ifdef __DEBUG_MODE
            
            for(int i = 0; i < list->size(); i++){
                UART2.writeln(list->at(i).c_str());
            }
        #endif
        if( m_memory->write(_MTEMP_SSID_ADDRESS         , list->at(1)) &&
            m_memory->write(_MTEMP_SSID_KEY_ADDRESS     , list->at(2)) &&
            m_memory->write(_MTEMP_MASTER_IP_ADDRESS    , list->at(3)) &&
            m_memory->write(_MTEMP_MASTER_PORT_ADDRESS  , list->at(4)) &&
            m_memory->write(_MTEMP_USERNAME_ADDRESS     , list->at(5)) &&
            m_memory->write(_MTEMP_USER_KEY_ADDRESS     , list->at(6))){
            
            #ifdef __DEBUG_MODE
            
                UART2.writeln("DATI SALVATI");
            #endif
        }
        
        delete list;
        return true;
    }
    
    return false;
}