
void initOscillator(void);
void initPorts(void);
void initInterrupts(void);

void initCpuClock(void);
void enableCpuClock(void);
void disableCpuClock(void);

void initSerial(void);
bool sendSerial(uint8_t character);
void sendChar(uint8_t character);
void sendString(uint8_t string[]);
char getSerial(void);
bool framingError(void);
bool overrunError(void);

void wait_ms(uint16_t time);
void binToString(uint8_t number, uint8_t string[]);