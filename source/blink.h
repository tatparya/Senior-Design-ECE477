int popo;

void outputMotorSteps();
void buttonpressed();
void testRobot();
void testKoc();
void testUART();

void createArray();
void createSolArray();

void initLEDs();
void initMotors();

void setup();

void SMCLKSetUp(const uint8_t freq);
void UARTA2Init(int baud_rate);
void UARTA2SendString(unsigned char* string);
void UARTA2SendByte(uint8_t byte);
