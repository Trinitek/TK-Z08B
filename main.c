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

    uint8_t addrString[9];
    addrString[8] = 0;
    uint8_t dataString[9];
    dataString[8] = 0;

    sendString(welcome);

    while(true) {
        binToString(addressBusInput, addrString);
        sendString(addrString);
        sendChar(' ');
        //binToString(dataBusInput, dataString);
        //sendString(dataString);
        //sendSerial(0x0D);
        eepromLed = !eepromLed;
        //sendSerial('A');
    }
}