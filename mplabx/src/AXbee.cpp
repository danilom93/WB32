#include "AXbee.h"

AFramework::AXbee::AXbee(AUARTDriver * driver, const AUARTDriver::Baud baud) : m_driver(NULL), m_flg(false){
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