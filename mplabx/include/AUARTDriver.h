/* 
 * File:   AUARTDriver.h
 * Author: Giuseppe
 *
 * Created on 16 giugno 2016, 22.45
 */

#ifndef AUARTDRIVER_H
#define	AUARTDRIVER_H

#include "ACommons.h"
#include "AString.h"
#include "ARegisterDefs.h"
#include "AInterruptSource.h"

namespace AFramework{
    
    class AUARTDriver{
        public:
            enum Baud{
                Baud9600,
                Baud19200,
                Baud115200,
            };
            
            enum Data{
                Data8bitNoParity,
                Data8bitEvenParity,
                Data9bitOddParity,
                Data9bitNoParity
            };
            
            enum StopSelection{
                Stop1bit,
                Stop2bit
            };
            
            AUARTDriver(volatile AUART_w * w, AInterruptSource * erInt, AInterruptSource * rxInt, AInterruptSource * txInt);
            bool open(const Baud baud, const Data dataLength, const StopSelection stop, const bool idleStop = false) volatile;
            bool isOpen() const;
            void close();
            AInterruptSource * getFaultEventController();
            AInterruptSource * getReceiverEventController();
            AInterruptSource * getTransmitEventController();
            bool write(const AString & str) volatile;
            
        private:
            volatile AUART_w * m_reg;
            AInterruptSource * m_erInt;
            AInterruptSource * m_rxInt;
            AInterruptSource * m_txInt;
                        bool   m_flg;
    };
    
#if __HAS_UART1__    
    extern volatile AUARTDriver UART1;
#endif

#if __HAS_UART2__
    extern volatile AUARTDriver UART2;
#endif
}

#endif	/* AUARTDRIVER_H */

