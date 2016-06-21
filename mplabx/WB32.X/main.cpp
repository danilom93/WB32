//#include "ACore.h"
//#include "ALcd.h"
//#include "APCF8563.h"
//
//#include <sys/attribs.h>
//
//
//using namespace AFramework;
//
//int main(int argc, char** argv) {
//    
//    System::init(16392, &PortB, bit15);
//    
//    APCF8563 clock(&I2C2);
//    
//    ALcd lcd(&PortC, bit0, &PortC, bit1, &PortC, bit2, &PortC, bit3, &PortC, bit4, &PortC, bit5, &PortC, bit6);
//    
//    System::delay(1000);
//    
//    lcd.lightOn();
//
//    lcd << "test";
//    
//    System::delay(1000);
//    if(clock.isGood()){
//        
//        lcd << "clock ok";
//    }else{
//        lcd << "clock fail";   
//    }
//    clock.setClockOut(APCF8563::Clock1Hz);
//    ADateTime tm;
//    while(1){
//        lcd.clear();
//        tm = clock.currentTime();
//        lcd << tm.timeToString();
//        System::delay(1000);
//    }
//}


#include "ACore.h"
#include "ALcd.h"
#include "AESP8266.h"
#include "A24LC512.h"
#include "APCF8563.h"
#include "AXbee.h"
#include "MTemp.h"
#include "MTempDefs.h"
#include <sys/attribs.h>

using namespace AFramework;

int main(int argc, char** argv) {
    
    System::init(16392, &PortB, bit15);
    
    AString str;
    
    ALcd lcd(&PortC, bit0, &PortC, bit1, &PortC, bit2, &PortC, bit3, &PortC, bit4, &PortC, bit5, &PortC, bit6);
    
        
    APCF8563    clock(&I2C2);
    
    System::delay(1000);
    
    lcd.lightOn();
        
    
    ADateTime tmp;
    lcd << "PROVA\n";
    clock.setClockOut(APCF8563::Clock1KHz);
    System::delay(1000);
    while(1){
        
        lcd.clear();
        tmp = clock.currentTime();
        lcd << "SONO LE ORE\n";
        lcd << tmp.timeToString();
        System::delay(1000);
    }
}