#ifndef MTEMPDEFS_H
#define MTEMPDEFS_H

#define _MTEMP_SSID_ADDRESS         0x00000000
#define _MTEMP_SSID_LENGTH          0x00000040

#define _MTEMP_SSID_KEY_ADDRESS     (_MTEMP_SSID_ADDRESS         + _MTEMP_SSID_LENGTH           )
#define _MTEMP_SSID_KEY_LENGTH      0x00000040

#define _MTEMP_MASTER_IP_ADDRESS    (_MTEMP_SSID_KEY_ADDRESS     + _MTEMP_SSID_KEY_LENGTH       )
#define _MTEMP_MASTER_IP_LENGTH     0x00000020

#define _MTEMP_MASTER_PORT_ADDRESS  (_MTEMP_MASTER_IP_ADDRESS    + _MTEMP_MASTER_IP_LENGTH      )
#define _MTEMP_MASTER_PORT_LENGTH   0x00000010

#define _MTEMP_USERNAME_ADDRESS     (_MTEMP_MASTER_PORT_ADDRESS  + _MTEMP_MASTER_PORT_LENGTH    )
#define _MTEMP_USERNAME_LENGTH      0x00000020

#define _MTEMP_USER_KEY_ADDRESS     (_MTEMP_USERNAME_ADDRESS     + _MTEMP_USERNAME_LENGTH       )
#define _MTEMP_USER_KEY_LENGTH      0x00000020

#define _MTEMP_ROOM_NUMBER_ADDRESS  (_MTEMP_USER_KEY_ADDRESS     + _MTEMP_USER_KEY_LENGTH       )
#define _MTEMP_ROOM_NUMBER_LENGTH   0x00000008

#define _MTEMP_PROGRAMDAY_LENGTH    0x00000001
#define _MTEMP_START_HOURS_LENGTH   0x00000002
#define _MTEMP_START_MINUTES_LENGTH 0x00000002
#define _MTEMP_END_HOURS_LENGTH     0x00000002
#define _MTEMP_END_MINUTES_LENGTH   0x00000002
#define _MTEMP_TARGET_TEMP_LENGTH   0x00000002
#define _MTEMP_ENABLED_LENGTH       0x00000001

#define _MTEMP_WEEKPROGRAM_VEC_SIZE 0x00000007
#define _MTEMP_ROOM_NAME_VEC_SIZE   0x00000020
#define _MTEMP_SENSOR_ADDR_LENGTH   0x00000007
#define _MTEMP_RELAY_OUT_LENGTH     0x00000007

#define _MTEMP_SEP_LENGTH           0x00000001
#define _NULL_CHAR_LENGTH           0x00000001 

#define _MTEMP_PROG_LENGTH          (_MTEMP_PROGRAMDAY_LENGTH    +   \
                                     _MTEMP_SEP_LENGTH           +   \
                                     _MTEMP_START_HOURS_LENGTH   +   \
                                     _MTEMP_SEP_LENGTH           +   \
                                     _MTEMP_START_MINUTES_LENGTH +   \
                                     _MTEMP_SEP_LENGTH           +   \
                                    _MTEMP_END_HOURS_LENGTH      +   \
                                    _MTEMP_SEP_LENGTH            +   \
                                    _MTEMP_END_MINUTES_LENGTH    +   \
                                    _MTEMP_SEP_LENGTH            +   \
                                    _MTEMP_TARGET_TEMP_LENGTH    +   \
                                    _MTEMP_SEP_LENGTH            +   \
                                    _MTEMP_ENABLED_LENGTH        +   \
                                    _NULL_CHAR_LENGTH            )


#define _MTEMP_ROOM_LENGTH          (_MTEMP_ROOM_NAME_VEC_SIZE   +  \
                                     _MTEMP_SEP_LENGTH           +  \
                                     _MTEMP_SENSOR_ADDR_LENGTH   +  \
                                     _MTEMP_SEP_LENGTH           +  \
                                     _MTEMP_RELAY_OUT_LENGTH     +  \
                                    _NULL_CHAR_LENGTH            )

#define _MTEMP_ROOM_0_ADDRESS       (_MTEMP_ROOM_NUMBER_ADDRESS  + _MTEMP_ROOM_NUMBER_LENGTH    )
#define _MTEMP_ROOM_0_PROG1_ADDRESS (_MTEMP_ROOM_0_ADDRESS       + _MTEMP_ROOM_LENGTH           )
#define _MTEMP_ROOM_0_PROG2_ADDRESS (_MTEMP_ROOM_0_PROG1_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_0_PROG3_ADDRESS (_MTEMP_ROOM_0_PROG2_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_0_PROG4_ADDRESS (_MTEMP_ROOM_0_PROG3_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_0_PROG5_ADDRESS (_MTEMP_ROOM_0_PROG4_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_0_PROG6_ADDRESS (_MTEMP_ROOM_0_PROG5_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_0_PROG7_ADDRESS (_MTEMP_ROOM_0_PROG6_ADDRESS + _MTEMP_PROG_LENGTH           )

#define _MTEMP_ROOM_1_ADDRESS       (_MTEMP_ROOM_0_PROG7_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_1_PROG1_ADDRESS (_MTEMP_ROOM_1_ADDRESS       + _MTEMP_ROOM_LENGTH           )
#define _MTEMP_ROOM_1_PROG2_ADDRESS (_MTEMP_ROOM_1_PROG1_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_1_PROG3_ADDRESS (_MTEMP_ROOM_1_PROG2_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_1_PROG4_ADDRESS (_MTEMP_ROOM_1_PROG3_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_1_PROG5_ADDRESS (_MTEMP_ROOM_1_PROG4_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_1_PROG6_ADDRESS (_MTEMP_ROOM_1_PROG5_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_1_PROG7_ADDRESS (_MTEMP_ROOM_1_PROG6_ADDRESS + _MTEMP_PROG_LENGTH           )

#define _MTEMP_ROOM_2_ADDRESS       (_MTEMP_ROOM_1_PROG7_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_2_PROG1_ADDRESS (_MTEMP_ROOM_2_ADDRESS       + _MTEMP_ROOM_LENGTH           )
#define _MTEMP_ROOM_2_PROG2_ADDRESS (_MTEMP_ROOM_2_PROG1_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_2_PROG3_ADDRESS (_MTEMP_ROOM_2_PROG2_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_2_PROG4_ADDRESS (_MTEMP_ROOM_2_PROG3_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_2_PROG5_ADDRESS (_MTEMP_ROOM_2_PROG4_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_2_PROG6_ADDRESS (_MTEMP_ROOM_2_PROG5_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_2_PROG7_ADDRESS (_MTEMP_ROOM_2_PROG6_ADDRESS + _MTEMP_PROG_LENGTH           )

#define _MTEMP_ROOM_3_ADDRESS       (_MTEMP_ROOM_2_PROG7_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_3_PROG1_ADDRESS (_MTEMP_ROOM_3_ADDRESS       + _MTEMP_ROOM_LENGTH           )
#define _MTEMP_ROOM_3_PROG2_ADDRESS (_MTEMP_ROOM_3_PROG1_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_3_PROG3_ADDRESS (_MTEMP_ROOM_3_PROG2_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_3_PROG4_ADDRESS (_MTEMP_ROOM_3_PROG3_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_3_PROG5_ADDRESS (_MTEMP_ROOM_3_PROG4_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_3_PROG6_ADDRESS (_MTEMP_ROOM_3_PROG5_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_3_PROG7_ADDRESS (_MTEMP_ROOM_3_PROG6_ADDRESS + _MTEMP_PROG_LENGTH           )

#define _MTEMP_ROOM_4_ADDRESS       (_MTEMP_ROOM_3_PROG7_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_4_PROG1_ADDRESS (_MTEMP_ROOM_4_ADDRESS       + _MTEMP_ROOM_LENGTH           )
#define _MTEMP_ROOM_4_PROG2_ADDRESS (_MTEMP_ROOM_4_PROG1_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_4_PROG3_ADDRESS (_MTEMP_ROOM_4_PROG2_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_4_PROG4_ADDRESS (_MTEMP_ROOM_4_PROG3_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_4_PROG5_ADDRESS (_MTEMP_ROOM_4_PROG4_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_4_PROG6_ADDRESS (_MTEMP_ROOM_4_PROG5_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_4_PROG7_ADDRESS (_MTEMP_ROOM_4_PROG6_ADDRESS + _MTEMP_PROG_LENGTH           )

#define _MTEMP_ROOM_5_ADDRESS       (_MTEMP_ROOM_4_PROG7_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_5_PROG1_ADDRESS (_MTEMP_ROOM_5_ADDRESS       + _MTEMP_ROOM_LENGTH           )
#define _MTEMP_ROOM_5_PROG2_ADDRESS (_MTEMP_ROOM_5_PROG1_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_5_PROG3_ADDRESS (_MTEMP_ROOM_5_PROG2_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_5_PROG4_ADDRESS (_MTEMP_ROOM_5_PROG3_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_5_PROG5_ADDRESS (_MTEMP_ROOM_5_PROG4_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_5_PROG6_ADDRESS (_MTEMP_ROOM_5_PROG5_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_5_PROG7_ADDRESS (_MTEMP_ROOM_5_PROG6_ADDRESS + _MTEMP_PROG_LENGTH           )

#define _MTEMP_ROOM_6_ADDRESS       (_MTEMP_ROOM_5_PROG7_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_6_PROG1_ADDRESS (_MTEMP_ROOM_6_ADDRESS       + _MTEMP_ROOM_LENGTH           )
#define _MTEMP_ROOM_6_PROG2_ADDRESS (_MTEMP_ROOM_6_PROG1_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_6_PROG3_ADDRESS (_MTEMP_ROOM_6_PROG2_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_6_PROG4_ADDRESS (_MTEMP_ROOM_6_PROG3_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_6_PROG5_ADDRESS (_MTEMP_ROOM_6_PROG4_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_6_PROG6_ADDRESS (_MTEMP_ROOM_6_PROG5_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_6_PROG7_ADDRESS (_MTEMP_ROOM_6_PROG6_ADDRESS + _MTEMP_PROG_LENGTH           )

#define _MTEMP_ROOM_7_ADDRESS       (_MTEMP_ROOM_6_PROG7_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_7_PROG1_ADDRESS (_MTEMP_ROOM_7_ADDRESS       + _MTEMP_ROOM_LENGTH           )
#define _MTEMP_ROOM_7_PROG2_ADDRESS (_MTEMP_ROOM_7_PROG1_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_7_PROG3_ADDRESS (_MTEMP_ROOM_7_PROG2_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_7_PROG4_ADDRESS (_MTEMP_ROOM_7_PROG3_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_7_PROG5_ADDRESS (_MTEMP_ROOM_7_PROG4_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_7_PROG6_ADDRESS (_MTEMP_ROOM_7_PROG5_ADDRESS + _MTEMP_PROG_LENGTH           )
#define _MTEMP_ROOM_7_PROG7_ADDRESS (_MTEMP_ROOM_7_PROG6_ADDRESS + _MTEMP_PROG_LENGTH           )

#define _MTEMP_DEFAULT_USERNAME     "root"
#define _MTEMP_DEFAULT_USER_KEY     "toor"
#define _MTEMP_STANDARD_AP_IP       "192.168.4.1"
#define _MTEMP_STANDARD_AP_PORT     0x1F40


#define _MTEMP_BOARD_OK             "[OK]"
#define _MTEMP_BOARD_FAIL           "[FAIL]"        //errore qualcosa 
#define _MTEMP_BOARD_ERROR          "[ERROR]"       //errore login

/*
 *  FORMATO STRINGA CONF
 *  (CLIENT)        SSID*KEY*IP*PORT*USER*PASSWORD*[CONF]
 */

#define _MTEMP_CONF                 "[CONF]"

/*
 *  FORMATO STRINGA TIMESET
 *  (CLIENT)        username*password*AA*MM*GG*WD*HH*MM*SS*[TIMESET]
 */
#define _MTEMP_TIMESET              "[TIMESET]"

/*
 *  FORMATO STRINGA TIMEGET
 *  (CLIENT)        username*password*[TIMEGET]
 *  (SERVER)        (AA*MM*GG*WD*HH*MM*SS*[OK] || [FAIL] || [ERROR])
 */
#define _MTEMP_TIMEGET              "[TIMEGET]"

/*
 *  FORMATO STRINGA TEMPGET
 *  (CLIENT)        username*password*R*[TEMPGET]
 *  (SERVER)        R*TT*([OK] || [FAIL] || [ERROR])
 *  (SERVER-NODO)   SENSOR*[TEMPGET]
 *  (NODO)          (SENSOR*TT*[OK] || [FAIL] || [ERROR])
 */
#define _MTEMP_TEMPGET              "[TEMPGET]"

/*
 *  FORMATO STRINGA ROOMSTAT
 *  (CLIENT)    username*password*R*[ROOMSTAT]
 *  (SERVER)    (R*NAME*ADDRESS*RELAYOUT*[OK] || [FAIL] || [ERROR])
 */
#define _MTEMP_ROOMSTAT             "[ROOMSTAT]"


/*
 *  FORMATO STRINGA PROGGET
 *  (CLIENT)    username*password*R*D*[PROGGET]
 *  (SERVER)    (R*D*HS*MS*HE*ME*TT*E*[OK] || [FAIL] || [ERROR])
 */
#define _MTEMP_PROGGET              "[PROGGET]"

/*
 *  FORMATO STRINGA PROGSET
 *  (CLIENT)    username*password*R*D*HS*MS*HE*ME*TT*E*[PROGSET]
 *  (SERVER)    ([OK] || [FAIL] || [ERROR])
 */
#define _MTEMP_PROGSET              "[PROGSET]"

/*
 *  FORMATO STRINGA FORCEON
 *  (CLIENT)    username*password*R*[FORCEON]
 *  (SERVER)    ([OK] || [FAIL] || [ERROR])
 */
#define _MTEMP_FORCEON              "[FORCEON]"

/*
 *  FORMATO STRINGA FORCEOFF
 *  (CLIENT)    username*password*R*[FORCEOFF]
 *  (SERVER)    ([OK] || [FAIL] || [ERROR])
 */
#define _MTEMP_FORCEOFF             "[FORCEOFF]"

#define _MTEMP_SEP                  '*'
#define _MTEMP_ENABLED              'Y'
#define _MTEMP_DISABLED             'N'

#define _MTEMP_WEEKPROGRAM_VEC_SIZE 0x00000007
#define _MTEMP_ROOM_NAME_VEC_SIZE   0x00000020
#define _MTEMP_ROOM_VEC_SIZE        0x00000008

    

/*  
 *  FORMATO STRINGA PROGRAMMA
 *  0000000000000000111
 *  0123456789ABCDEF012
 *  D*HS*MS*HE*ME*TT*E/
 */

/*
 *  FORMATO STRINGA STANZA
 *  000000000000000011111111111111112222222222222222
 *  0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF
 *  NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN*SSSSSSS*RRRRRRR
 */


#endif // MTEMPDEFS_H
