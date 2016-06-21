
#ifndef AXBEE_H
#define	AXBEE_H

#include "AUARTDriver.h"

namespace AFramework{

    class AXbee{
        public:
            
            AXbee(AUARTDriver * driver, const AUARTDriver::Baud baud = AUARTDriver::Baud9600);
            
        private:
            
            AUARTDriver * m_driver;
            bool          m_flg;
    };
}
#endif	/* AXBEE_H */

