#include <cstdlib>

#include "ACore.h"

using namespace AFramework;


int main(int argc, char** argv) {
    
    System::init(1024, &PortB, bit4);
    
    size_t heap1 = System::memstat();
    size_t heap2 = heap1;
    int * a;
    bool b1 = System::safeAlloc(&a, 1);
    bool b2 = b1;
    heap1 = System::memstat();
    heap2 = heap1;
    delete a;
    heap1 = System::memstat();
    heap2 = heap1;
    
    while(1){

    }
}

