
void initOscillator(void);
void initPorts(void);
void initInterrupts(void);

void initCpuClock(void);
void enableCpuClock(void);
void disableCpuClock(void);

void wait_ms(uint16_t time);
void binToString(uint8_t number, uint8_t string[]);