#include "ACore.h"
#include "ALcd.h"
#include "AESP8266.h"
#include "A24LC512.h"
#include "APCF8563.h"
#include "AXbee.h"
#include "MTemp.h"
#include "MTempDefs.h"
#include <sys/attribs.h>

#define __DEBUG_MODE

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
    
        
    APCF8563    clock(&I2C2);
    A24LC512    memory(&I2C2, 0);
    AESP8266    wlan(&UART1);
    AXbee       xbee(&UART2);
    
    MTempMaster app(&xbee, &clock, &memory, &wlan);
    
    UART1.getReceiverEventController()->enableInterrupt(Ip1, Isp0);
    
    
    #ifdef __DEBUG_MODE
                
        UART2.open(AUARTDriver::Baud9600, AUARTDriver::Data8bitNoParity, AUARTDriver::Stop1bit);
        System::outputMap(RPB10R, U2TXR);
        System::inputMap(RPA8R, U2RXR);  
    #endif
    
    System::outputMap(RPA0R, U1TXR);
    System::inputMap(RPA4R, U1RXR);
    
    System::delay(1000);
    
    lcd.lightOn();
        
    if(PortB.read(bit4) == Lo){
        
        if(app.networkConfig()){
            
            lcd << "Ho settato tutto";
            #ifdef __DEBUG_MODE
                
                UART2.writeln("LEGGO I DATI SALVATI");
                str.clear();
                if(memory.read(_MTEMP_SSID_ADDRESS, str)){
                    UART2.write("SSID = ");
                    UART2.writeln(str.c_str());
                    
                }else{
                    UART2.writeln("ERRORE");
                }
                
                str.clear();
                memory.read(_MTEMP_SSID_KEY_ADDRESS, str);
                UART2.write("PWD = ");
                UART2.writeln(str.c_str());
                str.clear();
                memory.read(_MTEMP_MASTER_IP_ADDRESS, str);
                UART2.write("IP = ");
                UART2.writeln(str.c_str());
                str.clear();
                memory.read(_MTEMP_MASTER_PORT_ADDRESS, str);
                UART2.write("PORT = ");
                UART2.writeln(str.c_str());
                str.clear();
                memory.read(_MTEMP_USERNAME_ADDRESS, str);
                UART2.write("USERNAME = ");
                UART2.writeln(str.c_str());
                str.clear();
                memory.read(_MTEMP_USER_KEY_ADDRESS, str);
                UART2.write("PASSWORD = ");
                UART2.writeln(str.c_str());
            
                
            #endif

        }
        
    }
    while(1);
}


