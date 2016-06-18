
#include "AESP8266.h"

#define __ESP_AT_TEST       "AT"
#define __ESP_AT_RST        "AT+RST"
#define __ESP_AT_ECHO_ON    "ATE1"
#define __ESP_AT_ECHO_OFF   "ATE0"
#define __ESP_AT_FIRMWARE   "AT+GMR"
#define __ESP_AT_MODE       "AT+CWMODE="
#define __ESP_AT_CONF_AP    "AT+CWSAP="
#define __ESP_AT_JOIN_AP    "AT+CWJAP="
#define __ESP_AT_LEAVE_AP   "AT+CWQAP"
#define __ESP_AT_LIST_AP    "AT+CWLAP"


#define __ESP_AT_OK         "OK"
#define __ESP_AT_READY      "ready"
#define __ESP_AT_ERROR      "ERROR"
#define __ESP_AT_FAIL       "FAIL"


AFramework::AESP8266::AESP8266(AUARTDriver * driver, const AUARTDriver::Baud baud) : m_driver(NULL), m_flg(false){
    /*  se il puntatore al driver è valido                                      */
    if(driver){
        /*  assegno il puntatore                                                */
        m_driver = driver;
        /*  se la seriale è chiusa                                              */
        if(!m_driver->isOpen()){
            /*  la apro ed assegno il risulato della open al flag               */
            m_flg = m_driver->open(baud, AUARTDriver::Data8bitNoParity, AUARTDriver::Stop1bit);
        }else{
            /*  se invece è aperta salvo sul flag il risultato del confronto    */
            /*  tra il baud passato e quello corrente                           */
            m_flg = (m_driver->baud() == baud);
        }
    }
}

bool AFramework::AESP8266::isOk(const uint32 ms) const{
    /*  se la seriale non è ok                                                  */
    if(!m_flg){
        /*  ritorno false                                                       */
        return false;
    }
    /*  pulisco il buffer                                                       */
    m_driver->bufferClear();
    /*  scrivo sulla seriale il comando                                         */
    m_driver->writeln(__ESP_AT_TEST);
    /*  ritorno il risultato del WDT                                            */
    return wdttmr(__ESP_AT_OK, ms);
}

bool AFramework::AESP8266::reset(const uint32 ms) const{
    /*  se la seriale non è ok                                                  */
    if(!m_flg){
        /*  ritorno false                                                       */
        return false;
    }
    /*  pulisco il buffer                                                       */
    m_driver->bufferClear();
    /*  scrivo sulla seriale il comando                                         */
    m_driver->writeln(__ESP_AT_RST);
    /*  ritorno il risultato del WDT                                            */
    return wdttmr(__ESP_AT_READY, ms);
}

bool AFramework::AESP8266::setEcho(const bool echo, const uint32 ms) const{
    /*  se la seriale non è ok                                                  */
    if(!m_flg){
        /*  ritorno false                                                       */
        return false;
    }
    m_driver->bufferClear();
    /*  scrivo sulla seriale il comando                                         */
    m_driver->writeln((echo ? __ESP_AT_ECHO_ON : __ESP_AT_ECHO_OFF));
    /*  ritorno il risultato del WDT                                            */
    return wdttmr(__ESP_AT_OK, ms);    
}

bool AFramework::AESP8266::version(AString & str, const uint32 ms) const{
    bool res = false;
    /*  se la seriale non è ok                                                  */
    if(!m_flg){
        /*  ritorno false                                                       */
        return false;
    }
    m_driver->bufferClear();
    /*  scrivo sulla seriale il comando                                         */
    m_driver->writeln(__ESP_AT_FIRMWARE);
    /*  salvo il risultato del WDT                                              */
    res = wdttmr(__ESP_AT_OK, ms);
    /*  se il flag è ok                                                         */
    if(res){
        str = m_driver->read();
        while(str.remove(__ESP_AT_OK) || str.remove(" ") || str.remove("\r") || str.remove("\n"));
    }
    return res;
}

bool AFramework::AESP8266::setMode(const ESPMode mode, const bool rst, const uint32 ms) const{
    AString str = __ESP_AT_MODE;
    bool res = false;
    /*  se la seriale non è ok                                                  */
    if(!m_flg){
        /*  ritorno false                                                       */
        return false;
    }
    m_driver->bufferClear();
    switch(mode){
        case StationMode:
        case APMode:
        case BothMode:
            str += static_cast<char>(mode + 0x30);
            break;
        default:
            return false;
            break;
    }
    /*  scrivo sulla seriale il comando                                         */
    m_driver->writeln(str.c_str());
    /*  salvo il risultato del WDT                                              */
    res = wdttmr(__ESP_AT_OK, ms);
    /*  se non deve essere resettato o l'operazione è fallita                   */
    if(!rst){
        /*  ritorno il risultato di del WDT                                     */
        return res;
    }
    /*  se l'operazione precedente è andata male                                */
    if(!res){
        /*  ritorno false                                                       */
        return res;
    }
    /*  ritorno il risultato di reset                                           */
    return reset();
}


bool AFramework::AESP8266::configureAP(const AString & ssid, const AString & pwd, const uint8 channel, const uint32 ms) const{
    AString str = __ESP_AT_CONF_AP;
    /*  controllo che il canale sia valido e che la seriale sia ok              */
    if(channel > 0x0B || !m_flg){
        /*  se non è così ritorno false                                         */
        return false;
    }
    /*  accodo il nome                                                          */
    str += "\"";
    str += ssid;
    /*  accodo la password                                                      */
    str += "\",\"";
    str += pwd;
    /*  accodo il canale                                                        */
    str += "\",";
    str += static_cast<char>(channel + 0x30);
    /*  accodo il tipo di cifratura                                             */
    str += ",";
    str += (pwd.isEmpty() ? static_cast<char>(0 + 0x30) : static_cast<char>(4 + 0x30));
    /*  pulisco il buffer                                                       */
    m_driver->bufferClear();
    /*  scrivo sulla seriale il comando                                         */
    m_driver->writeln(str.c_str());
    /*  ritorno il risultato del WDT                                            */
    return wdttmr(__ESP_AT_OK, ms); 
}

bool AFramework::AESP8266::joinAP(const AString & ssid, const AString & pwd, const uint32 ms) const{
    AString str = __ESP_AT_JOIN_AP;
    /*  controllo che la seriale sia ok                                         */
    if(!m_flg){
        /*  se non è così ritorno false                                         */
        return false;
    }
    /*  accodo il nome                                                          */
    str += "\"";
    str += ssid;
    /*  accodo la password                                                      */
    str += "\",\"";
    str += pwd;
    /*  accodo il canale                                                        */
    str += "\"";
    /*  pulisco il buffer                                                       */
    m_driver->bufferClear();
    /*  scrivo sulla seriale il comando                                         */
    m_driver->writeln(str.c_str());
    /*  ritorno il risultato del WDT                                            */
    return wdttmr(__ESP_AT_OK, ms);    
}

bool AFramework::AESP8266::leaveAP(const uint32 ms) const{
    /*  controllo che la seriale sia ok                                         */
    if(!m_flg){
        /*  se non è così ritorno false                                         */
        return false;
    }
    /*  pulisco il buffer                                                       */
    m_driver->bufferClear();
    /*  scrivo sulla seriale il comando                                         */
    m_driver->writeln(__ESP_AT_LEAVE_AP);
    /*  ritorno il risultato del WDT                                            */
    return wdttmr(__ESP_AT_OK, ms);  
}


bool AFramework::AESP8266::availableAP(AString & res, const uint32 ms) const{
    bool flag = false;
    /*  controllo che la seriale sia ok                                         */
    if(!m_flg){
        /*  se non è così ritorno false                                         */
        return false;
    }
    /*  pulisco il buffer                                                       */
    m_driver->bufferClear();
    /*  scrivo sulla seriale il comando                                         */
    m_driver->writeln(__ESP_AT_LIST_AP);
    /*  salvo il risultato del WDT                                              */
    flag = wdttmr(__ESP_AT_OK, ms);
    /*  salvo il buffer                                                         */
    res = m_driver->read();
    /*  ritorno il flag                                                         */
    return flag;
}

bool AFramework::AESP8266::wdttmr(const char * str, const uint32 ms) const{
    bool res1 = false;
    bool res2 = false;
    /*  prendo il tempo di sistema                                              */
    ATime deadline = System::aliveTime();
    /*  aggiungo il timeout                                                     */
    deadline += ms;
    /*  fino a che il tempo non è scaduto                                       */
    while(System::aliveTime() <= deadline){
        /*  controllo che nel buffer ci sia la stringa cercata                  */
        res1 = m_driver->bufferContains(str);
        /*  controllo che nel buffer ci sia FAIL oppure ERROR                   */
        res2 = (m_driver->bufferContains(__ESP_AT_FAIL) || 
                m_driver->bufferContains(__ESP_AT_ERROR));
        
        /*  se ho trovato il token                                              */
        if(res1){
            /*  esco dal loop                                                   */
            break;
        }
        /*  se il buffer contiene fail o error                                  */
        if(res2){
            /*  ritorno subito false                                            */
            return false;
        }
    }
    /*  ritorno il flag                                                         */
    return res1;
}
