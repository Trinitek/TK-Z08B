
#include <xc.h>
#include <stdint.h>
#include "ports.h"

void interrupt ISR(void) {
    // check for timer0 overflow
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        cpuClockOutput = !cpuClockOutput;   // invert clock output
        INTCONbits.TMR0IF = 0;      // clear overflow flag
    }
}