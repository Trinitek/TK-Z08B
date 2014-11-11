
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

// Read-only memory bank
uint8_t memory[0xFF];

uint8_t readByte(uint8_t address) {
    return memory[address];
}

bool writeByte(uint8_t byte, uint8_t address) {
    if (address < 0x38 || 0x40 < address) {
        memory[address] = byte;
        return true;
    } else return false;
}

uint8_t readEeprom(uint8_t highAddr, uint8_t lowAddr) {
    EECON1bits.EEPGD = 0;       // select EEPROM
    EECON1bits.CFGS = 0;        // access EEPROM memory
    EEADR = lowAddr;            // set address
    EEADRH = highAddr;
    EECON1bits.RD = 1;          // initiate read
    return EEDATA;
}

bool writeEeprom(uint8_t byte, uint8_t highAddr, uint8_t lowAddr) {
    EECON1bits.EEPGD = 0;       // select EEPROM over Flash
    EECON1bits.CFGS = 0;        // access EEPROM memory over Config bits
    EECON1bits.FREE = 0;        // write only
    EECON1bits.WREN = 1;        // enable write cycles
    EEADR = lowAddr;            // set address
    EEADRH = highAddr;
    EEDATA = byte;              // set byte
    EECON1bits.WR = 1;          // initiate write
    return !EECON1bits.WRERR;   // true if successful
}