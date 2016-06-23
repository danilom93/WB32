#ifndef MTEMP_H
#define	MTEMP_H

#include "A24LC512.h"
#include "AESP8266.h"
#include "APCF8563.h"
#include "AString.h"
#include "AXbee.h"
#include "ALcd.h"
#include "MTempDefs.h"
#include "MTempCommons.h"

namespace AFramework{
    
    class MTempMaster{
        
        public:
                    MTempMaster(AXbee * xbee, APCF8563 *clk, A24LC512 *mem, AESP8266 *wifi, ALcd *lcd, volatile AHardwarePort *port);
            
            bool    networkConfig();
            bool    run();
            
            
        private:

                        AESP8266 *      m_wifi;
                        A24LC512 *      m_memory;
                        AXbee    *      m_xbee;
                        APCF8563 *      m_clk;
                        ALcd     *      m_lcd;   
                        bool            m_flag;
                        Room            m_rooms[_MTEMP_ROOM_VEC_SIZE];
            volatile    AHardwarePort * m_port;
            
            bool    saveNetworkConfig(const AString &data);
            bool    prepareAp(const AString &ssid, const AString &pwd, const uint16 port);
            void    checkPrograms();
            bool    defaultProgram();
            bool    joinNetwork();
            bool    newLoginRequest();
            bool    connectionHandler();
            bool    programsManager();
    };
}

#endif	/* MTEMP_H */

