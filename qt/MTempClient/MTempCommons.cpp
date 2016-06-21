#include "MTempCommons.h"

/**
 * @brief AFramework::Program::Program
 */

AFramework::Program::Program() : m_weekday(ADataTime::Sunday),
                                 m_startHours(0),
                                 m_startMinutes(0),
                                 m_endHours(23),
                                 m_endMinutes(59),
                                 m_targetTemp(25),
                                 m_enabled(false){

}

AFramework::Program::Program(const AFramework::ADataTime::Weekdays wDay,
                             const quint8 sHours,
                             const quint8 sMinutes,
                             const quint8 eHours,
                             const quint8 eMinutes,
                             const quint8 targetTemp,
                             const quint8 en,
                             bool  &ok) : Program(){

    ok = (setWeekday(wDay)               &&
          setStartHours(sHours)          &&
          setStartMinutes(sMinutes)      &&
          setEndHours(eHours)            &&
          setEndMinutes(eMinutes)        &&
          setTargetTemperature(targetTemp));

    if(ok){
        if(en){
            setEnabled();
        }else{
            setDisabled();
        }
    }
}

AFramework::Program::Program(const QString &wDay,
                             const QString &sHours,
                             const QString &sMinutes,
                             const QString &eHours,
                             const QString &eMinutes,
                             const QString &targetTemp,
                             const QString &en,
                             bool  &ok) : Program(){

    ok = (setWeekday(wDay)                 &&
          setStartHours(sHours)            &&
          setStartMinutes(sMinutes)        &&
          setEndHours(eHours)              &&
          setEndMinutes(eMinutes)          &&
          setTargetTemperature(targetTemp) &&
          (en.size() == 1 && (en[0] == _MTEMP_ENABLED || en[0] == _MTEMP_DISABLED)));

    if(ok){
        if(en[0] == _MTEMP_ENABLED){
            setEnabled();
        }else{
            setDisabled();
        }
    }
}

AFramework::Program::Program(const QString & program, bool &ok) : Program(){

    fromString(program, ok);
}

bool AFramework::Program::fromString(const QString &program, bool &ok){

    QString wDay;
    QString sHours;
    QString sMinutes;
    QString eHours;
    QString eMinutes;
    QString en;
    QString targetTemp;

    if(program.size() != 0x12){

        ok = false;
    }else{
        wDay       += program[0x00];
        sHours     += program[0x02];
        sHours     += program[0x03];
        sMinutes   += program[0x05];
        sMinutes   += program[0x06];
        eHours     += program[0x08];
        eHours     += program[0x09];
        eMinutes   += program[0x0B];
        eMinutes   += program[0x0C];
        targetTemp += program[0x0E];
        targetTemp += program[0x0F];
        en         += program[0x11];
    }

    ok = (setWeekday(wDay)                 &&
          setStartHours(sHours)            &&
          setStartMinutes(sMinutes)        &&
          setEndHours(eHours)              &&
          setEndMinutes(eMinutes)          &&
          setTargetTemperature(targetTemp) &&
          (en.size() == 1 && (en[0] == _MTEMP_ENABLED || en[0] == _MTEMP_DISABLED)));

    if(ok){
        if(en[0] == _MTEMP_ENABLED){
            setEnabled();
        }else{
            setDisabled();
        }
    }
}

AFramework::ADataTime::Weekdays AFramework::Program::weekday() const{

    return m_weekday;
}

quint8 AFramework::Program::startHours() const{

    return m_startHours;
}

quint8 AFramework::Program::startMinutes() const{

    return m_startMinutes;
}

quint8 AFramework::Program::endHours() const{

    return m_endHours;
}

quint8 AFramework::Program::endMinutes() const{

    return m_endMinutes;
}

quint8 AFramework::Program::targetTemperature() const{

    return m_targetTemp;
}

bool AFramework::Program::isEnabled() const{

    return m_enabled;
}

bool AFramework::Program::setWeekday(const AFramework::ADataTime::Weekdays wDay){

    if(wDay == ADataTime::NoWeekday){

        return false;
    }

    m_weekday = wDay;

    return true;
}

bool AFramework::Program::setWeekday(const QString &str){
#   ifdef ANTIPODE32MR

    if(str.size() != 1){

        return false;
    }

    if((static_cast<quint8>(str[0] - 0x30) >  7) ||
        static_cast<quint8>(str[0] - 0x30) == 0) {

        return false;
    }

    m_weekday = static_cast<ADataTime::Weekdays>(str[0] - 0x30);

    return true;

#   else

    if(str.size() != 1){

        return false;
    }

    if((static_cast<quint8>(str[0].toLatin1() - 0x30) >  7) ||
        static_cast<quint8>(str[0].toLatin1() - 0x30) == 0) {

        return false;
    }

    m_weekday = static_cast<ADataTime::Weekdays>(str[0].toLatin1() - 0x30);

    return true;

#   endif
}

bool AFramework::Program::setStartHours(const quint8 sHours){

    if(sHours > 23 || sHours > m_endHours){

        return false;
    }

    if(sHours == m_endHours && m_startMinutes > m_endMinutes){

        return false;
    }

    m_startHours = sHours;

    return true;
}

bool AFramework::Program::setStartHours(const QString &str){
#   ifdef ANTIPODE32MR

    if(str.size() != 2){

        return false;
    }

    return setStartHours((static_cast<quint8>(str[0] - 0x30) * 10) +
                          static_cast<quint8>(str[1] - 0x30));

#   else

    if(str.size() != 2){

        return false;
    }

    return setStartHours((static_cast<quint8>(str[0].toLatin1() - 0x30) * 10) +
                          static_cast<quint8>(str[1].toLatin1() - 0x30));

#   endif
}

bool AFramework::Program::setStartMinutes(const quint8 sMinutes){

    if(sMinutes > 59){

        return false;
    }

    if(sMinutes >= m_endMinutes && m_startHours == m_endHours){

        return false;
    }

    m_startMinutes = sMinutes;

    return true;
}

bool AFramework::Program::setStartMinutes(const QString &str){
#   ifdef ANTIPODE32MR

    if(str.size() != 2){

        return false;
    }

    return setStartMinutes((static_cast<quint8>(str[0] - 0x30) * 10) +
                            static_cast<quint8>(str[1] - 0x30));

#   else

    if(str.size() != 2){

        return false;
    }

    return setStartMinutes((static_cast<quint8>(str[0].toLatin1() - 0x30) * 10) +
                            static_cast<quint8>(str[1].toLatin1() - 0x30));

#   endif
}

bool AFramework::Program::setEndHours(const quint8 eHours){

    if(eHours > 23 || eHours < m_startHours){

        return false;
    }

    if(eHours == m_startHours && m_endMinutes < m_startMinutes){

        return false;
    }

    m_endHours = eHours;

    return true;
}

bool AFramework::Program::setEndHours(const QString &str){
#   ifdef ANTIPODE32MR

    if(str.size() != 2){

        return false;
    }

    return setEndHours((static_cast<quint8>(str[0] - 0x30) * 10) +
                        static_cast<quint8>(str[1] - 0x30));

#   else

    if(str.size() != 2){

        return false;
    }

    return setEndHours((static_cast<quint8>(str[0].toLatin1() - 0x30) * 10) +
                        static_cast<quint8>(str[1].toLatin1() - 0x30));

#   endif
}

bool AFramework::Program::setEndMinutes(const quint8 eMinutes){

    if(eMinutes > 59){

        return false;
    }

    if(eMinutes <= m_endMinutes && m_startHours == m_endHours){

        return false;
    }

    m_endMinutes = eMinutes;

    return true;
}

bool AFramework::Program::setEndMinutes(const QString &str){
#   ifdef ANTIPODE32MR

    if(str.size() != 2){

        return false;
    }

    return setEndMinutes((static_cast<quint8>(str[0] - 0x30) * 10) +
                          static_cast<quint8>(str[1] - 0x30));

#   else

    if(str.size() != 2){

        return false;
    }

    return setEndMinutes((static_cast<quint8>(str[0].toLatin1() - 0x30) * 10) +
                          static_cast<quint8>(str[1].toLatin1() - 0x30));

#   endif
}

bool AFramework::Program::setTargetTemperature(const quint8 targetTemp){

    if(targetTemp > 40 || targetTemp < 18){

        return false;
    }

    m_targetTemp = targetTemp;

    return true;
}

bool AFramework::Program::setTargetTemperature(const QString &str){
#   ifdef ANTIPODE32MR

    if(str.size() != 2){

        return false;
    }

    return setTargetTemperature((static_cast<quint8>(str[0] - 0x30) * 10) +
                                 static_cast<quint8>(str[1] - 0x30));

#   else

    if(str.size() != 2){

        return false;
    }

    return setTargetTemperature((static_cast<quint8>(str[0].toLatin1() - 0x30) * 10) +
                                 static_cast<quint8>(str[1].toLatin1() - 0x30));

#   endif
}

void AFramework::Program::setEnabled(){

    m_enabled = false;
}

void AFramework::Program::setDisabled(){

    m_enabled = true;
}

QString AFramework::Program::toString() const{

    QString str;

    str += static_cast<char>(m_weekday                  + 0x30);
    str += _MTEMP_SEP;
    str += static_cast<char>((m_startHours      / 0x0A) + 0x30);
    str += static_cast<char>((m_startHours      % 0x0A) + 0x30);
    str += _MTEMP_SEP;
    str += static_cast<char>((m_startMinutes    / 0x0A) + 0x30);
    str += static_cast<char>((m_startMinutes    % 0x0A) + 0x30);
    str += _MTEMP_SEP;
    str += static_cast<char>((m_endHours        / 0x0A) + 0x30);
    str += static_cast<char>((m_endHours        % 0x0A) + 0x30);
    str += _MTEMP_SEP;
    str += static_cast<char>((m_endMinutes      / 0x0A) + 0x30);
    str += static_cast<char>((m_endMinutes      % 0x0A) + 0x30);
    str += _MTEMP_SEP;
    str += static_cast<char>((m_targetTemp      / 0x0A) + 0x30);
    str += static_cast<char>((m_targetTemp      % 0x0A) + 0x30);
    str += _MTEMP_SEP;
    str += (m_enabled ? _MTEMP_ENABLED : _MTEMP_DISABLED      );

    return str;

}

/**
 * @brief AFramework::Room::Room
 */

#ifdef ANTIPODE32MR
    AFramework::quint16 AFramework::Room::m_ROOM_BASE_ADDR(_MTEMP_ROOM_0_ADDRESS);
#else

#endif

AFramework::Room::Room(){

}
