
#include "ACore.h"
#include "AUARTDriver.h"

#include <cstring>

#if __HAS_UART1__
    AFramework::AInterruptSource U1er(_IFSVEC_U1EIF_POSITION , _IECVEC_U1EIE_POSITION , _IPCVEC_U1IP_POSITION, _IFS_U1EIF_MASK , _IEC_U1EIE_MASK , _IPC_U1IP_POSITION, _IPC_U1IS_POSITION);
    AFramework::AInterruptSource U1rx(_IFSVEC_U1RXIF_POSITION, _IECVEC_U1RXIE_POSITION, _IPCVEC_U1IP_POSITION, _IFS_U1RXIF_MASK, _IEC_U1RXIE_MASK, _IPC_U1IP_POSITION, _IPC_U1IS_POSITION);
    AFramework::AInterruptSource U1tx(_IFSVEC_U1TXIF_POSITION, _IECVEC_U1TXIE_POSITION, _IPCVEC_U1IP_POSITION, _IFS_U1TXIF_MASK, _IEC_U1TXIE_MASK, _IPC_U1IP_POSITION, _IPC_U1IS_POSITION);
    extern volatile AFramework::AUART_w UART1_w __asm__("UART1_w") __attribute__((section("sfrs")));
    AFramework::AUARTDriver AFramework::UART1(&UART1_w, &U1er, &U1rx, &U1tx);
#endif

#if __HAS_UART2__
    AFramework::AInterruptSource U2er(_IFSVEC_U2EIF_POSITION , _IECVEC_U2EIE_POSITION , _IPCVEC_U2IP_POSITION, _IFS_U2EIF_MASK , _IEC_U2EIE_MASK , _IPC_U2IP_POSITION, _IPC_U2IS_POSITION);
    AFramework::AInterruptSource U2rx(_IFSVEC_U2RXIF_POSITION, _IECVEC_U2RXIE_POSITION, _IPCVEC_U2IP_POSITION, _IFS_U2RXIF_MASK, _IEC_U2RXIE_MASK, _IPC_U2IP_POSITION, _IPC_U2IS_POSITION);
    AFramework::AInterruptSource U2tx(_IFSVEC_U2TXIF_POSITION, _IECVEC_U2TXIE_POSITION, _IPCVEC_U2IP_POSITION, _IFS_U2TXIF_MASK, _IEC_U2TXIE_MASK, _IPC_U2IP_POSITION, _IPC_U2IS_POSITION);
    extern volatile AFramework::AUART_w UART2_w __asm__("UART2_w") __attribute__((section("sfrs")));
    AFramework::AUARTDriver AFramework::UART2(&UART2_w, &U2er, &U2rx, &U2tx);
#endif
    
AFramework::AUARTDriver::AUARTDriver(volatile AUART_w * w, AInterruptSource * erInt, AInterruptSource * rxInt, AInterruptSource * txInt) : m_reg(w), m_erInt(erInt), m_rxInt(rxInt), m_txInt(txInt), m_index(0), m_flg(false) {
    /*  chiamo close                                                            */
    close();
}

bool AFramework::AUARTDriver::open(const Baud baud, const Data dataLength, const StopSelection stop, const bool idleStop){
    
    uint32 tmpBaud = 0;
    uint32 tmpConf = 0;
    /*  imposto il baudd rate per il calcolo del valore da mettere nel registro */
    switch(baud){
        case Baud9600:
            /*  9600                                                            */
            tmpBaud = 0x00002580;
            break;
        case Baud19200:
            /*  19200                                                           */
            tmpBaud = 0x00004B00;
            break;
        case Baud115200:
            /*  115200                                                          */
            tmpBaud = 0x0001C200;
            break;
    };
    /*  configuro per abilitare il modulo con l'eventuale bit di idle           */
    tmpConf |= _UxMODE_ON_MASK | (idleStop ? _UxMODE_SIDL_MASK : 0x00000000);
    /*  imposto i bit di stop                                                   */
    switch(stop){
        case Stop1bit:
            /*  1bit                                                            */
            tmpConf |= static_cast<uint8>(Stop1bit);
            break;
        case Stop2bit:
            /*  2bit                                                            */
            tmpConf |= static_cast<uint8>(Stop2bit);
            break;
    }
    /*  configuro la lunghezza del dato                                         */
    switch(dataLength){
        case Data8bitNoParity:
            tmpConf |= (static_cast<uint8>(Data8bitNoParity)   << _UxMODE_PDSEL_POSITION);
            break;
        case Data8bitEvenParity:
            tmpConf |= (static_cast<uint8>(Data8bitEvenParity) << _UxMODE_PDSEL_POSITION); 
            break;
        case Data9bitOddParity:
            tmpConf |= (static_cast<uint8>(Data9bitOddParity)  << _UxMODE_PDSEL_POSITION);
            break;
        case Data9bitNoParity:
            tmpConf |= (static_cast<uint8>(Data9bitNoParity)   << _UxMODE_PDSEL_POSITION);
            break;
    }
    /*  imposto il baudrate                                                     */
    m_reg->UxBRG.SET  = (System::busFrequency() / (16 * tmpBaud)) - 1;
    /*  accendo il modulo                                                       */
    m_reg->UxMODE.SET = tmpConf;
    /*  attivo rx e tx                                                          */
    m_reg->UxSTA.SET = (_UxSTA_URXEN_MASK | _UxSTA_UTXEN_MASK);
    /*  imposto il flag                                                         */
    m_flg = true;
    /*  cancello il buffer                                                      */
    clearBuffer();
    /*  10 ms di ritarto                                                        */
    System::delay(10);
    /*  ritorno true                                                            */
    return true;
}

bool AFramework::AUARTDriver::isOpen() const{
    /*  ritorno il flag                                                         */
    return m_flg;
}

void AFramework::AUARTDriver::close(){
    /*  cancello il registro MODE                                               */
    m_reg->UxMODE.CLR = Quick::All;
    /*  cancello il registro STAT                                               */
    m_reg->UxSTA.CLR = Quick::All;
    /*  cancello il registro TX                                                 */
    m_reg->UxTXREG.REG = Quick::All;
    /*  cancello il registro RX                                                 */
    m_reg->UxRXREG.REG = Quick::All;
    /*  cancello il registro BRG                                                */
    m_reg->UxBRG.CLR = Quick::All;
    /*  pulisco il buffer                                                       */
    clearBuffer();
    /*  metto a false il flag                                                   */
    m_flg = false;
}

AFramework::AInterruptSource * AFramework::AUARTDriver::getFaultEventController() volatile{
    /*  ritorno il gestore dell'interrupt per il fault                          */
    return m_erInt;    
}

AFramework::AInterruptSource * AFramework::AUARTDriver::getReceiverEventController() volatile{
    /*  ritorno il gestore dell'interrupt per rx                                */
    return m_rxInt;
}

AFramework::AInterruptSource * AFramework::AUARTDriver::getTransmitEventController() volatile{
    /*  ritorno il gestore dell'interrupt per rx                                */
    return m_txInt;
}

bool AFramework::AUARTDriver::write(const AString & str){
    /*  se la seriale � chiusa                                                  */
    if(!m_flg){
        /*  ritorno false                                                       */
        return false;
    }
    for(uint32 i = 0; i < str.size(); i++){
        /*  aspetto che il buffer di trasmissione si sia svuotato               */
        while(m_reg->UxSTA.REG & _UxSTA_UTXBF_MASK);
        /*  carico il dato nel registro                                         */
        m_reg->UxTXREG.REG = str[i];
        /*  aspetto che il registro a scorrimento sia vuoto                     */
        while(!(m_reg->UxSTA.REG & _UxSTA_TRMT_MASK));
    }
    /*  ritorno true                                                            */
    return true;    
}

AFramework::AString AFramework::AUARTDriver::read() const{
    /*  ritorno il buffer                                                       */    
    return m_buffer;
}

bool AFramework::AUARTDriver::bufferContains(const AString & pattern, const bool & cs){
    /*  ritorno il confronto                                                    */
    return (std::strstr(m_buffer, pattern.c_str()) != NULL);
}

void AFramework::AUARTDriver::rxHandler(){
    /*  controllo che l'interrupt sia in ricezione                              */
    if(!(m_rxInt->hasInterruptOccurred())){
        /*  se non � cos� ritorno                                               */
        return;
    }
    /*  se rischio di bucare il buffer                                          */
    if(m_index >= __UART_BUFFER_SIZE__ - 1){
        /*  cancello il buffer                                                  */
        clearBuffer();
    }
    /*  aggiungo il carattere ricevuto al buffer                                */
    m_buffer[m_index++] = static_cast<char>(m_reg->UxRXREG.REG & 0xFF);
    /*  azzero il flag dell'interrupt                                           */
    m_rxInt->clearFlag();
}

size_t AFramework::AUARTDriver::bytesAvailable() const{
    /*  ritorno la dimensione del buffer                                        */
    return std::strlen(m_buffer);
}

void AFramework::AUARTDriver::clearBuffer(){
    /*  azzero l'indice                                                         */
    m_index = 0;
    /*  cancello il buffer di lettura                                           */
    std::memset(m_buffer, 0x00, __UART_BUFFER_SIZE__);
}