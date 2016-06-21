#ifndef MTEMPCOMMONS_H
#define MTEMPCOMMONS_H

#define _MTEMP_SEP                  '*'
#define _MTEMP_ENABLED              'Y'
#define _MTEMP_DISABLED             'N'

#include "MTempDefs.h"
#include "ASystemConfig.h"

#ifdef ANTIPODE32MR

#   include "AString.h"
#   include "ADateTime.h"
#   include "A24LC512.h"

    namespace AFramework{

        typedef AString     QString;
        typedef uint8       quint8;
        typedef uint16      quint16;
        typedef uint32      quint32;

    }

#else

#   include <QString>

    namespace AFramework{

        class ADateTime{

            public:

                enum Weekdays{
                    NoWeekday,
                    Sunday,
                    Monday,
                    Tuesday,
                    Wednesday,
                    Thursday,
                    Friday,
                    Saturday
                };
        };

    }

#endif



namespace AFramework{

    class Program{
        public:
            Program();

            Program(const ADateTime::Weekdays wDay,
                    const quint8 sHours,
                    const quint8 sMinutes,
                    const quint8 eHours,
                    const quint8 eMinutes,
                    const quint8 targetTemp,
                    const quint8 en,
                    bool  & ok);

            Program(const QString & wDay,
                    const QString & sHours,
                    const QString & sMinutes,
                    const QString & eHours,
                    const QString & eMinutes,
                    const QString & targetTemp,
                    const QString & en,
                    bool  & ok);
            Program(const QString & program, bool & ok);

            bool fromString(const QString & program, bool & ok);

            ADateTime::Weekdays weekday() const;
            quint8 startHours() const;
            quint8 startMinutes() const;
            quint8 endHours() const;
            quint8 endMinutes() const;
            quint8 targetTemperature() const;
            bool   isEnabled() const;

            bool setWeekday(const ADateTime::Weekdays wDay);
            bool setWeekday(const QString & str);

            bool setStartHours(const quint8 sHours);
            bool setStartHours(const QString & str);

            bool setStartMinutes(const quint8 sMinutes);
            bool setStartMinutes(const QString & str);

            bool setEndHours(const quint8 eHours);
            bool setEndHours(const QString & str);

            bool setEndMinutes(const quint8 eMinutes);
            bool setEndMinutes(const QString & str);

            bool setTargetTemperature(const quint8 targetTemp);
            bool setTargetTemperature(const QString & str);

            void setEnabled();
            void setDisabled();

            QString toString() const;

        private:
            ADateTime::Weekdays m_weekday;
            quint8              m_startHours;
            quint8              m_startMinutes;
            quint8              m_endHours;
            quint8              m_endMinutes;
            quint8              m_targetTemp;
            bool                m_enabled;
    };

    class Room{

        public:

            enum RoomNumber{
                Room0,
                Room1,
                Room2,
                Room3,
                Room4,
                Room5,
                Room6,
                Room7
            };

            Room();

            #ifdef ANTIPODE32MR

            Room(A24LC512 * eeprom, const RoomNumber roomNum, bool & ok);
            void    loadRoom();
            void    saveRoom();
            bool    loadProgram(const ADateTime::Weekdays day);
            bool    saveProgram(const ADateTime::Weekdays day);
            quint8  currentTemp() const;

            #endif

            Room(const QString & name, const QString & sensorAddress, const QString relayOut, bool & ok);

            QString roomName() const;
            QString sensorAddress() const;
            quint32 relayOut() const;
            Program program(const ADateTime::Weekdays day) const;

            bool    setRoomName(const QString & name);
            bool    setSensorAddress(const quint8 addr);
            bool    setRelayOut(const quint32 gpio);
            bool    setProgram(const ADateTime::Weekdays day, const QString & str);

            QString toString() const;

        private:
            static  quint16 m_ROOM_BASE_ADDR;
                    char    m_roomName      [_MTEMP_ROOM_NAME_VEC_SIZE  ];
                    Program m_weekProgram   [_MTEMP_WEEKPROGRAM_VEC_SIZE];
                    quint8  m_sensorAddrees;
                    quint32 m_relayOut;
    };

}

#endif // MTEMPCOMMONS_H
