#include <math.h>
#include "ACore.h"
#include "AUARTDriver.h"
#include "AI2CDriver.h"
#include <sys/attribs.h>

using namespace AFramework;

extern "C"{
    
    void __ISR(_UART_1_VECTOR, IPL1AUTO) UART_HANDLER(){
        
        UART1.rxHandler();
    }
}

int main(int argc, char** argv) {
    
    System::init(128, &PortB, bit4);
    AString str;

    UART1.open(AUARTDriver::Baud115200, AUARTDriver::Data8bitNoParity, AUARTDriver::Stop1bit);
    UART1.getReceiverEventController()->enableInterrupt(Ip1, Isp0);
    
    System::outputMap(RPA0R, U1TXR);
    System::inputMap(RPA4R, U1RXR);
    
    while(1){
        
        if(UART1.bufferContains("\r\n")){
            str = UART1.read();
            str += "\nMemoria: ";
            str += AString(static_cast<sint32>(System::memstat()));
            str += "\r\n";
            if(!str.good()){
                switch(str.lastError()){
                    case AErrorNotifier::NoMemory:
                        UART1.write("Memoria finita\r\n");
                        break;
                    default:
                        UART1.write("Altro\r\n");
                        break;
                }
            }else{
               UART1.write(str.c_str()); 
            }
            
            UART1.clearBuffer();
        }
    }
}


