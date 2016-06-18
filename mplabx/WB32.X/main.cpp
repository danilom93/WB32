#include "ACore.h"
#include "ALcd.h"
#include "AESP8266.h"

#include <sys/attribs.h>


using namespace AFramework;

extern "C"{
    
    void __ISR(_UART_1_VECTOR, IPL1AUTO) UART_HANDLER(){
        
        UART1.rxHandler();
    }
}

int main(int argc, char** argv) {
    
    System::init(16392, &PortB, bit15);
    
    AString str;
    
    ALcd lcd(&PortC, bit0, &PortC, bit1, &PortC, bit2, &PortC, bit3, &PortC, bit4, &PortC, bit5, &PortC, bit6);
    
    AESP8266 wlan(&UART1);
    
    UART1.getReceiverEventController()->enableInterrupt(Ip1, Isp0);
    
    System::outputMap(RPA0R, U1TXR);
    System::inputMap(RPA4R, U1RXR);
    
    System::delay(1000);
    
    lcd.lightOn();

    while(1){
        lcd.clear();
        lcd << "MEM: " <<AString(static_cast<sint32>(System::memstat()));
        System::delay(2000);
        if(wlan.isOk()){
            lcd.clear();
            lcd << "Modulo ok";
            System::delay(1000);
            lcd.clear();
            lcd << "Configuro\nstazione...";
            System::delay(1000);

            if(wlan.setMode(AESP8266::StationMode)){
                lcd.clear();
                lcd << "Stazione OK!";
                System::delay(1000);
                
                if(wlan.joinAP("AndroidAP", "danilom93")){
                    lcd.clear();
                    lcd << "Connesso!\n";
                    System::delay(1000);
                    lcd << "Lascio AP...";
                    
                    if(wlan.leaveAP()){
                        lcd.clear();
                        lcd << "AP lasciato.";
                        System::delay(1000);      
                        
                    }else{
                        
                        lcd.clear();
                        lcd << "Errore AP.";
                        System::delay(1000);                        
                    }
                }else{
                    
                    lcd.clear();
                    lcd << "Non Connesso!";
                    System::delay(1000);
                }
            }else{
                
                lcd.clear();
                lcd << "Stazione\nFallita!";
            }
        }else{
            
            lcd.clear();
            lcd << "ESP FAIL...";
        }
        System::delay(2000);
    }
}


