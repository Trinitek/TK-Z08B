
void initSerial(void);
bool sendSerial(uint8_t character);
void sendChar(uint8_t character);
void sendString(uint8_t string[]);
char getSerial(void);
bool framingError(void);
bool overrunError(void);