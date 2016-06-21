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
    
    System::init(16392, &PortB, bit4);
    
    bool test = true;
    
//    ALcd lcd(&PortC, bit0, &PortC, bit1, &PortC, bit2, &PortC, bit3, &PortC, bit4, &PortC, bit5, &PortC, bit6);
    
    PortB.setOutput(bit10 | bit11);
        

    
    System::delay(1000);

    while(1){
        
        
        if(test){
            PortB.write(bit10, Hi);
            PortB.write(bit11, Lo);
            test = false;
        }else{
            PortB.write(bit10, Lo);
            PortB.write(bit11, Hi);
            test = true;
        }
       
        System::delay(1000);
    }
}