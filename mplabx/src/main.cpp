
#include "ASystemConfig.h"
#include "ACore.h"
#include "ALcd.h"
#include "APCF8563.h"
#include "ADateTime.h"
#include "A24LC512.h"
#include "AString.h"
#include "AUARTDriver.h"

using namespace std;
using namespace AFramework;

int main(){

    System::init(16392, &PortB, bit15);
    
    AString test;
    ADateTime tm;
    APCF8563 clock(&I2C2);
    A24LC512 mem(&I2C2, 0);
    ALcd lcd(&PortC, bit0, &PortC, bit1, &PortC, bit2, &PortC, bit3, &PortC, bit4, &PortC, bit5, &PortC, bit6);
    
    tm.setYear(16);
    tm.setMonth(ADateTime::June);
    tm.setDayOfMonth(29);
    tm.setWeekday(ADateTime::Wednesday);
    tm.setHours(9);
    tm.setMinutes(0);
    tm.setSeconds(0);
    
    lcd.lightOn();
    
    
    System::delay(1000);
    
    lcd.clear();
    
    clock.setClockOut(APCF8563::Clock1Hz);
    
    if(!clock.isGood()){
        AString tmp = "prima scarica...";
        lcd << "Batteria scarica" << endl;
        lcd << "Imposto l'ora...";
        clock.setTime(tm);
        System::delay(1000);
        lcd.clear();
        lcd << "Ora impostata!";
        mem.write(0, tmp);
        System::delay(1000);
    }
    
    mem.read(0, test);

    while(1){
        lcd.clear();
        tm = clock.currentTime();
        lcd << "    " << tm.timeToString();
        lcd.setLine(1);
        if(test.good()){
            lcd << test;
        }else{
            lcd << "Errore";
        }
        System::delay(1000);
    }
    return 0;
}
