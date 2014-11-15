#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "system.h"
#include "ports.h"

void main(void) {

    initPorts();
    initOscillator();
    initInterrupts();
    initSerial();
    initCpuClock();
    
    enableCpuClock();

    char welcome[] =
        "\n\n"
        "TK-Z08B Computer BIOS Controller\n"
        "Software version 0.1-24AUG2014\n"
        "Controller: 8 MHz | CPU: 2 MHz\n"
        "Serial: 2400 baud\n"
        "\n";
    //uint8_t greet[] = "Hello world! ";
    //uint8_t halted[] = "Halted. ";
    //uint8_t rxChar;

    uint8_t addrString[9];
    addrString[8] = 0;

    uint8_t linefeed[] = { 0x0D,0 };

    sendString(welcome);

    while(true) {
        // Convert address bus signals to writable binary string
        /*if (a0Input) addrString[7] = '1'; else addrString[7] = '0';
        if (a1Input) addrString[6] = '1'; else addrString[6] = '0';
        if (a2Input) addrString[5] = '1'; else addrString[5] = '0';
        if (a3Input) addrString[4] = '1'; else addrString[4] = '0';
        if (a4Input) addrString[3] = '1'; else addrString[3] = '0';
        if (a5Input) addrString[2] = '1'; else addrString[2] = '0';
        if (a6Input) addrString[1] = '1'; else addrString[1] = '0';
        if (a7Input) addrString[0] = '1'; else addrString[0] = '0';
        sendString(addrString);*/
        binToString(addressBusInput, addrString);
        sendString(addrString);
        sendString(linefeed);
    }
}

bool checkForMemoryRead(void) {
    if (cpuClockOutput == 1 && 0); // TODO
    return false;
}