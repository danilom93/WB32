#ifndef MTEMP_H
#define	MTEMP_H

#include "A24LC512.h"
#include "AESP8266.h"
#include "APCF8563.h"
#include "AXbee.h"
#include "AString.h"

namespace AFramework{
    
    class MTempMaster{
        
        public:
                    MTempMaster(AXbee * xbee, APCF8563 *clk = NULL, A24LC512 *mem = NULL, AESP8266 *wifi = NULL);
            bool    prepareAp(const AString &ssid, const AString &pwd, const uint16 port);
            bool    firstConfig();
            
        private:
           
            AESP8266 * m_wifi;
            A24LC512 * m_memory;
            AXbee    * m_xbee;
            APCF8563 * m_clk;
            bool       m_flag;
            
            
    };
}

#endif	/* MTEMP_H */

