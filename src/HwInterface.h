#define TOGGLE_LED_PIN D0 

#define KEY1_PIN D3
#define KEY2_PIN D4
#define KEY3_PIN D5


void hwSetup(void);
void hwLoop(void);

bool hwSecoundTick(void);
unsigned long hwGetMillis(void);
