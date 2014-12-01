
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * Send an 8-bit character over RS-232 if the transmit shift register is empty
 * @param character
 * @return true if successful
 */
bool sendSerial(uint8_t character) {
    if (TXSTAbits.TRMT) {
        TXREG = character;
        return true;
    } else {
        return false;
    }
}

/**
 * Force send an 8-bit character over RS-232
 * @param character
 */
void sendChar(uint8_t character) {
    while (!sendSerial(character));
}

/**
 * Send a string of 8-bit characters over RS-232
 * @param string - array of characters
 */
void sendString(uint8_t string[]) {
    int i = 0;
    while(string[i] != 0) {
        sendChar(string[i]);
        i++;
    }
}

/**
 * Get a character sent over RS-232 that is waiting in the receiver FIFO
 * @return character
 */
uint8_t getSerial(void) {
    // If a byte was not received, return 0
    if (PIR1bits.RC1IF) return RCREG;
    else return 0;
}

/**
 * Get true/false flag of the FramingError bit for the RX receiver
 *
 * @return value of RCSTAbits.FERR
 */
bool framingError(void) {
    return RCSTAbits.FERR;
}

/**
 * Get true/false flag of the OverrunError bit for the RX receiver
 *
 * @return value of RCSTAbits.OERR
 */
bool overrunError(void) {
    return RCSTAbits.OERR;
}

/**
 * Clear the OverrunError bit for the RX receiver
 */
void clearOverrunError(void) {
    RCSTAbits.CREN = 0;
}
