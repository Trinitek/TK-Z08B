
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "memory.h"

// input to CPU
    // interrupt code
#define interruptIn         0
    // RS-232
#define serialConfigIn      1
#define serialByteIn        3
    // EEPROM
#define eepromAddrIn        7
#define eepromDataIn        8

// output from CPU
    // RS-232
#define serialConfigOut     1
#define serialByteOut       2
    // EEPROM
#define eepromAddrOut       7
#define eepromDataOut       8

uint8_t interruptCode;
uint8_t eepromAddrSelect = 0;
uint8_t eepromAddrHigh;
uint8_t eepromAddrLow;

void triggerInterrupt(uint8_t code) {
    interruptCode = code;
    // TODO
}

uint8_t readDevice(uint8_t port) {
    switch(port) {
        default: return 0;
        case interruptIn:
            return interruptCode;
        case eepromAddrIn:
            if (eepromAddrSelect % 2 == 0) {
                eepromAddrSelect++;
                return eepromAddrHigh;
            } else {
                eepromAddrSelect++;
                return eepromAddrLow;
            }
        case eepromDataIn:
            return readEeprom(eepromAddrHigh, eepromAddrLow);
    }
}

bool writeDevice(uint8_t byte, uint8_t port) {
    switch(port) {
        default: return false;
        case eepromAddrOut:
            if (eepromAddrSelect % 2 == 0) {
                eepromAddrSelect++;
                eepromAddrHigh = byte;
            } else {
                eepromAddrSelect++;
                eepromAddrLow = byte;
            } return true;
        case eepromDataOut:
            writeEeprom(byte, eepromAddrHigh, eepromAddrLow);
            return true;
    }
}