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
    uint8_t halted[] = "Halted. ";
    uint8_t rxChar;

    sendString(welcome);

    while(true) {
        //eepromLed = !eepromLed;
        //dataBusOutput = 0x76;
        //if (haltInput == 0) sendString(halted);
        //else sendSerial('.');
        //wait_ms(5000);
        rxChar = getSerial();
        if (rxChar != 0) sendSerial(rxChar);
    }
}

bool checkForMemoryRead(void) {
    if (cpuClockOutput == 1 && 0); // TODO
    return false;
}