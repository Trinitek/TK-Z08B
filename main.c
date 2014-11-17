#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "system.h"
#include "ports.h"

void main(void) {

    initPorts();
    initOscillator();
    //initInterrupts();
    initSerial();
    initCpuClock();
    
    enableCpuClock();

    char welcome[] =
        "\n\n"
        "TK-Z08B Computer BIOS Controller\n"
        "Software version 0.2-16NOV2014\n"
        "Controller: 8 MHz | CPU: 2 MHz\n"
        "Serial: 2400 baud\n"
        "\n";

    uint8_t addrString[9];
    addrString[8] = 0;
    uint8_t dataString[9];
    dataString[8] = 0;

    sendString(welcome);

    while(true) {
        // Display CPU clock state
        (cpuClockOutput) ? (sendChar('I')) : (sendChar('O'));
        sendChar(' ');

        // Dispaly HALT state
        (!haltInput) ? (sendChar('h')) : (sendChar('-'));
        sendChar(' ');

        // Display M1 state
        (!m1Input) ? (sendChar('1')) : (sendChar('-'));
        sendChar(' ');

        // Display MEMRQ state
        (!memrqInput) ? (sendChar('r')) : (sendChar('-'));
        sendChar(' ');

        // Display IORQ state
        (!iorqInput) ? (sendChar('q')) : (sendChar('-'));
        sendChar(' ');

        // Display WAIT state
        (!waitInput) ? (sendChar('w')) : (sendChar('-'));
        sendChar(' ');

        // Display BUSRQ state
        (!busrqInput) ? (sendChar('u')) : (sendChar('-'));
        sendChar(' ');

        // Display BUSACK state
        (!busackInput) ? (sendChar('a')) : (sendChar('-'));
        sendChar(' ');

        // Display RD state
        (!readInput) ? (sendChar('R')) : (sendChar('-'));
        sendChar(' ');

        // Display WR state
        (!writeInput) ? (sendChar('W')) : (sendChar('-'));
        sendChar(' ');

        // Display memory CE state
        (ramEnableInput) ? (sendChar('C')) : (sendChar('-'));
        sendChar(' ');

        // Display low byte of address bus
        binToString(addressBusInput, addrString);
        sendString(addrString);
        sendChar(' ');

        // Display data bus
        binToString(dataBusInput, dataString);
        sendString(dataString);
        sendChar(0x0D);
        
        // Toggle clock output
        cpuClockOutput = !cpuClockOutput;

        // Toggle LED output
        eepromLed = !eepromLed;
    }
}