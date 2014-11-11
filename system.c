
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "ports.h"

#define in          1
#define out         0

/* SYSTEM CONFIGURATION BITS */
// CONFIG1H
#pragma config FOSC = INTIO67   // Oscillator Selection bits (Internal oscillator block)
#pragma config PLLCFG = OFF     // 4X PLL Enable (Oscillator used directly)
#pragma config PRICLKEN = ON    // Primary clock enable bit (Primary clock is always enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRTEN = OFF     // Power-up Timer Enable bit (Power up timer disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 190       // Brown Out Reset Voltage bits (VBOR set to 1.90 V nominal)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (Watch dog timer is always disabled. SWDTEN has no effect.)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC1  // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<5:0> pins are configured as analog input channels on Reset)
#pragma config CCP3MX = PORTB5  // P3A/CCP3 Mux bit (P3A/CCP3 input/output is multiplexed with RB5)
#pragma config HFOFST = ON      // HFINTOSC Fast Start-up (HFINTOSC output and ready status are not delayed by the oscillator stable status)
#pragma config T3CMX = PORTC0   // Timer3 Clock input mux bit (T3CKI is on RC0)
#pragma config P2BMX = PORTD2   // ECCP2 B output mux bit (P2B is on RD2)
#pragma config MCLRE = EXTMCLR  // MCLR Pin Enable bit (MCLR pin enabled, RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled if MCLRE is also 1)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0 (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection Block 1 (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection Block 2 (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection Block 3 (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection Block 2 (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection Block 3 (Block 3 (00C000-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection Block 2 (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection Block 3 (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

void initOscillator(void) {
    OSCCONbits.IRCF = 0b110;    // 8 MHz
}

void initPorts(void) {
    // disable all analog functionality
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
    ANSELE = 0;

    // initialize TRISbits for address bus
    addressBusTris = in;

    // initialize TRISbits for data bus
    dataBusTris = out;

    // initialize TRISbits for control ports
    cpuClockTris = out;
    intTris = out;
    busrqTris = out;
    readTris = in;
    writeTris = in;
    waitTris = in;
    haltTris = in;
    iorqTris = in;
    memrqTris = in;
    busackTris = in;

    // setup starting output data
    cpuClockOutput = 0;
    intOutput = 1;
    busrqOutput = 1;

    // initialize TRISbits for status indicators
    eepromLedTris = out;
}

void initInterrupts(void) {
    INTCONbits.GIE = 1;         // enable all interrupts globally
    INTCONbits.PEIE = 1;        // enable all peripherial interrupts
}

void initCpuClock(void) {
    T0CONbits.T08BIT = 1;       // 8-bit mode
    T0CONbits.T0CS = 0;         // use internal instruction cycle clock
    T0CONbits.PSA = 0;          // enable prescaler
    T0CONbits.T0PS = 0b001;     // 8 MHz / 4 = 2 MHz
    INTCONbits.TMR0IE = 1;      // enable interrupt on overflow
}

void enableCpuClock(void) {
    T0CONbits.TMR0ON = 1;       // enable timer
}

void disableCpuClock(void) {
    T0CONbits.TMR0ON = 0;       // disable timer
}

void initSerial(void) {
    // setup transmission
    TXSTAbits.TX9 = 0;          // 8-bit transmission
    TXSTAbits.TXEN = 1;         // enable transmission
    TXSTAbits.SYNC = 0;         // asynchronous
    TXSTAbits.BRGH = 0;         // low speed baud rate

    // setup reception
    RCSTAbits.SPEN = 1;         // enable serial port
    RCSTAbits.RX9 = 0;          // 8-bit reception
    RCSTAbits.CREN = 1;         // continuously receive data

    // setup baud generator
    BAUDCONbits.SCKP = 0;       // do not invert data on transmission
    BAUDCONbits.BRG16 = 0;      // use 8-bit generator
    BAUDCONbits.ABDEN = 0;      // disable baud detect
    SPBRG1 = 51;                // 2400 baud at 8 MHz
    SPBRGH1 = 0;
}

/**
 * Send an 8-bit character over RS-232 if the transmit shift register is empty
 * @param character
 * @return true if successful
 */
bool sendSerial(char character) {
    if (TXSTAbits.TRMT) {
        TXREG = character;
        return true;
    } else {
        return false;
    }
}

/**
 * Send a string of 8-bit characters over RS-232
 * @param string - array of characters
 */
void sendString(uint8_t string[]) {
    int i = 0;
    while(string[i] != 0) {
        while(sendSerial(string[i]) == 0);
        i++;
    }
}

/**
 * Get a character sent over RS-232 and is waiting in the receiver FIFO
 * @return character
 */
char getSerial(void) {
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

void wait_ms(uint16_t time) {
    static long timel = 0;
    timel = time * 10;
    for (; timel; timel--);
}