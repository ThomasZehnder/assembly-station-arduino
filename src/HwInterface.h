#define TOGGLE_LED_PIN D0 

//D1 = SDL for OLED display
//D2 = SDA for OLED display

//D3 = WS2812 data line (LEDS need 5V, signal only 3.3V works)

//D4 is reserved for build In led -> show http activity
 

#define KEY1_PIN D5
#define KEY2_PIN D6
#define KEY3_PIN D7


void hwSetup(void);
void hwLoop(void);

bool hwSecoundTick(void);
bool hwCentiSecoundTick(void);
unsigned long hwGetMillis(void);

bool keyPressed(int keyNumber);
int keyPressedCounter(int keyNumber);
