#include"ADht22.h"

AFramework::ADht22::ADht22(volatile AHardwarePort *port, const uint32 pin){
    
    m_port = port;
    m_pin  = pin;
}

AFramework::ADht22::ATempHum AFramework::ADht22::read(const uint32 ms){
    
    ADht22::ATempHum res;
    
    uint8 bits[40] = {0};
    float raws[40] = {0};
    signed char i = 0;

    res.hum = 0;
    res.temp = 0;
    
    m_port->setOutput(m_pin);
    m_port->write(m_pin, Lo);

    System::delay(1);
    
    m_port->write(m_pin, Hi);
    
    Timer1.setSynchronousInternal16(0.001);
    Timer1.reset();
    Timer1.open();
    while(Timer1.elapsedTime() < 0.00003);
    Timer1.close();
    
    m_port->write(m_pin, Lo);
    m_port->setInput(m_pin);
   
    while(!m_port->read(m_pin));
    while(m_port->read(m_pin));
    
    for(i = 0; i < 40; i++){
        
        Timer1.reset();
        while(!m_port->read(m_pin));
        Timer1.open();
        while(m_port->read(m_pin));
        Timer1.close();
        raws[i] = Timer1.elapsedTime();
    }

    for(i = 0; i < 40; i++){
        bits[i] = (raws[i] > 0.000036 ? 1 : 0);
    }
    for(i = 15; i >= 0; i--){
        if(bits[i]){
            res.hum += (bits[i] << (15 - i));
        }
    }
    for(i = 31; i >= 17; i--){
        if(bits[i]){
            res.temp += (bits[i] << (31 - i));
        }
    }
    if(bits[16]){
        res.temp *= -1;
    }
    res.hum /= 10;
    res.temp /= 10;
    return res;
}