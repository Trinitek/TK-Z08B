
/* ADDRESS BUS CONFIGURATION */
    // direction
#define addressBusTris      TRISA

    // outgoing
#define a0Output            LATAbits.LATA0
#define a1Output            LATAbits.LATA1
#define a2Output            LATAbits.LATA2
#define a3Output            LATAbits.LATA3
#define a4Output            LATAbits.LATA4
#define a5Output            LATAbits.LATA5
#define a6Output            LATAbits.LATA6
#define a7Output            LATAbits.LATA7
#define addressBusOutput    LATA

    // incoming
#define a0Input             PORTAbits.RA0
#define a1Input             PORTAbits.RA1
#define a2Input             PORTAbits.RA2
#define a3Input             PORTAbits.RA3
#define a4Input             PORTAbits.RA4
#define a5Input             PORTAbits.RA5
#define a6Input             PORTAbits.RA6
#define a7Input             PORTAbits.RA7
#define addressBusInput     PORTA

/* DATA BUS CONFIGURATION */
    // direction
#define dataBusTris         TRISD

    // outgoing
#define d0Output            LATDbits.LATD0
#define d1Output            LATDbits.LATD1
#define d2Output            LATDbits.LATD2
#define d3Output            LATDbits.LATD3
#define d4Output            LATDbits.LATD4
#define d5Output            LATDbits.LATD5
#define d6Output            LATDbits.LATD6
#define d7Output            LATDbits.LATD7
#define dataBusOutput       LATD

    // incoming
#define d0Input             PORTDbits.RD0
#define d1Input             PORTDbits.RD1
#define d2Input             PORTDbits.RD2
#define d3Input             PORTDbits.RD3
#define d4Input             PORTDbits.RD4
#define d5Input             PORTDbits.RD5
#define d6Input             PORTDbits.RD6
#define d7Input             PORTDbits.RD7
#define dataBusInput        PORTD

/* SYSTEM CONTROL PORT DONFIGURATION */
    // direction
#define cpuClockTris        TRISEbits.TRISE0
#define readTris            TRISCbits.TRISC5
#define writeTris           TRISCbits.TRISC4
#define waitTris            TRISBbits.TRISB4
#define intTris             TRISCbits.TRISC0
#define haltTris            TRISCbits.TRISC1
#define iorqTris            TRISCbits.TRISC2
#define memrqTris           TRISCbits.TRISC3
#define busrqTris           TRISEbits.TRISE1
#define busackTris          TRISEbits.TRISE2
#define ramEnableTris       TRISBbits.TRISB2
#define m1Tris              TRISBbits.TRISB1
#define cpuResetTris        TRISBbits.TRISB0

    // outgoing
#define cpuClockOutput      LATEbits.LATE0
#define intOutput           LATCbits.LATC0
#define busrqOutput         LATEbits.LATE1
#define cpuResetOutput      LATBbits.LATB0
#define waitOutput          LATBbits.LATB4

    // incoming
#define readInput           PORTCbits.RC5
#define writeInput          PORTCbits.RC4
#define waitInput           PORTBbits.RB4
#define haltInput           PORTCbits.RC1
#define iorqInput           PORTCbits.RC2
#define memrqInput          PORTCbits.RC3
#define busrqInput          PORTEbits.RE1
#define busackInput         PORTEbits.RE2
#define ramEnableInput      PORTBbits.RB2
#define m1Input             PORTBbits.RB1
#define cpuResetInput       PORTBbits.RB0

/* STATUS INDICATOR CONFIGURATION */
    // direction
#define eepromLedTris       TRISBbits.TRISB5

    // outgoing
#define eepromLed           LATBbits.LATB5

// serialTX = C6
// serialRX = C7
