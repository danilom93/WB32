#include "MTemp.h"

#define _MTemp_SSID_AP  "MTemp"
#define _MTemp_PWD_AP   "802.15.4"
#define _MTemp_PORT_AP  8000

//#define __DEBUG_MODE

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
    #ifdef __DEBUG_MODE
            
        UART2.writeln("ERRORE IN prepareAP!!!!!!!!!!!!!!!!");
    #endif
    return false;
}

bool AFramework::MTempMaster::firstConfig(){
    
    if(prepareAp(_MTemp_SSID_AP, _MTemp_PWD_AP, _MTemp_PORT_AP)){
        
        #ifdef __DEBUG_MODE
            
            UART2.writeln("ESP IN ATTESA DI CONNESSIONI");
        #endif

        
    }
}