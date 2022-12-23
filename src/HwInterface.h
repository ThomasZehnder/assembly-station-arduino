#define TOGGLE_LED_PIN D0 

//D4 is reserved for build In led

#define KEY1_PIN D3
#define KEY2_PIN D5
#define KEY3_PIN D6


void hwSetup(void);
void hwLoop(void);

bool hwSecoundTick(void);
unsigned long hwGetMillis(void);
