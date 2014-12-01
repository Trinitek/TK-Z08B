
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "system.h"
#include "ports.h"
#include "serial.h"
#include "device.h"

void displayAddress(void);

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
        "Software version 0.2-16NOV2014\n"
        "Controller: 8 MHz | CPU: 2 MHz\n"
        "Serial: 2400 baud\n"
        "\n";

    uint8_t addrString[9];
    addrString[8] = 0;
    uint8_t dataString[9];
    dataString[8] = 0;

    uint8_t program[] = {
        0x21, 0x0F, 0x00, 0x7E, 0xFE, 0x00, 0xCA, 0x00, 0x00, 0xD3, 0x02, 0x23, 0xC3, 0x03, 0x00, 0x48,
        0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x21, 0x20, 0x00
    };

    sendString(welcome);

    while (true) {

        // If #WR or CE is active, switch databus to input
        if (ramEnableInput || !writeInput) dataBusTris = 0xFF;
        else dataBusTris = 0x00;

        // If #WR and #IORQ are active, send data to device handler
        if (!writeInput || !iorqInput) writeDevice(dataBusInput, addressBusInput);

        // Write to databus latches regardless of the TRIS status
        dataBusOutput = program[addressBusInput];
    }
}