// Include the correct display library

// For a connection via I2C using the Arduino Wire include:
#include <Wire.h>        // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" // legacy: #include "SSD1306.h"

// Initialize the OLED display using Arduino Wire:
SSD1306Wire display(0x3c, SDA, SCL); // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h e.g. https://github.com/esp8266/Arduino/blob/master/variants/nodemcu/pins_arduino.h

#include "Oled.h"

#include "Global.h"

// start pixel of blue area
#define Y_OFFSET 16
//"table line 1"
#define X_OFFSET_1 54

#define DEMO_DURATION 3000
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 1;
void drawStartScreen();

void oledSetup()
{

    Serial.println("OledSetup --> Start");

    // Initialising the UI will init the display too.
    display.init();

    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);

    // clear the display
    display.clear();
    drawStartScreen();
    display.display();

    Serial.println("OledSetup --> End");
}

void drawStartScreen()
{
    // Font Demo1
    // create more fonts at http://oleddisplay.squix.ch/
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Assembly-001");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0 + Y_OFFSET, "Search WLAN");
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 16 + Y_OFFSET, "avm.swiss");
}

void drawRebootScreen()
{
    // Font Demo1
    // create more fonts at http://oleddisplay.squix.ch/
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Assembly-001");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0 + Y_OFFSET, "Reboot active");
    // display.setFont(ArialMT_Plain_24);
    // display.drawString(0, 16 + Y_OFFSET, "avm.swiss");

    int progress = (counter / 5) % 100;
    // draw the progress bar
    display.drawProgressBar(0, 32 + Y_OFFSET, 120, 10, progress);
}

void drawProgressScreen()
{
    // Font Demo1
    // create more fonts at http://oleddisplay.squix.ch/
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Assembly-001");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0 + Y_OFFSET, "Job working");

    int progress = (counter / 5) % 100;
    // draw the progress bar
    display.drawProgressBar(0, 20 + Y_OFFSET, 120, 10, progress);

    display.setFont(ArialMT_Plain_10);
    // Draw Assembly State
    display.drawString(0, Y_OFFSET + 36, "Assembly State: ");
    display.drawString(X_OFFSET_1 + 24, Y_OFFSET + 36, Assembly.getProcessState());
}

void drawWlanOkScreen()
{
    // Draw a line horizontally
    display.drawHorizontalLine(0, Y_OFFSET - 1, 128); // last yellow

    // Draw actual millis top right
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.drawString(128, 0, String(millis())); // top right

    // Draw ip
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 0, Assembly.localIp); // top right


    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0 + Y_OFFSET, "WLAN ok-wait job");

    int progress = (counter / 5) % 100;
    // draw the progress bar
    display.drawProgressBar(0, 20 + Y_OFFSET, 120, 10, progress);

    display.setFont(ArialMT_Plain_10);
    // Draw Assembly State
    display.drawString(0, Y_OFFSET + 36, "Assembly State: ");
    display.drawString(X_OFFSET_1 + 24, Y_OFFSET + 36, Assembly.getProcessState());
}


void drawProgressBarDemo()
{
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "OLED Demo running");

    int progress = (counter / 5) % 100;
    // draw the progress bar
    display.drawProgressBar(0, Y_OFFSET + 24, 120, 10, progress);

    // draw the percentage as String
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, Y_OFFSET, String(progress) + "%");
}

void drawAssemblyInfo()
{
    // Draw a line horizontally
    display.drawHorizontalLine(0, Y_OFFSET - 1, 128); // last yellow

    // Draw actual millis top right
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.drawString(128, 0, String(millis())); // top right

    // Draw ip
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 0, Assembly.localIp); // top right

    // Draw Connection Status
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, Y_OFFSET, "Wifi On: ");                                  // top right
    display.drawString(X_OFFSET_1, Y_OFFSET, String(Assembly.wifiConnected));      // top right
    display.drawString(0, Y_OFFSET + 12, "MQTT On: ");                             // top right
    display.drawString(X_OFFSET_1, Y_OFFSET + 12, String(Assembly.mqttConnected)); // top right

    // Draw Key Counter
    display.drawString(0, Y_OFFSET + 24, "Key [1,2,3]: ");                                            // top right
    display.drawString(X_OFFSET_1, Y_OFFSET + 24, String(Assembly.keys[0].pressedCounter));           // top right
    display.drawString(X_OFFSET_1 + 24, Y_OFFSET + 24, String(Assembly.keys[1].pressedCounter));      // top right
    display.drawString(X_OFFSET_1 + 24 + 24, Y_OFFSET + 24, String(Assembly.keys[2].pressedCounter)); // top right
    // Draw Key Counter
    display.drawString(0, Y_OFFSET + 36, "Assembly State: ");                       // top right
    display.drawString(X_OFFSET_1 + 24, Y_OFFSET + 36, Assembly.getProcessState()); // top right
}

// Demo demos[] = {drawStartScreen, drawTextFlowDemo, drawTextAlignmentDemo, drawRectDemo, drawProgressBarDemo};
Demo demos[] = {drawAssemblyInfo, drawProgressBarDemo};
int demoLength = (sizeof(demos) / sizeof(Demo));
long timeSinceLastModeSwitch = 0;

void oledLoop()
{
    // clear the display
    display.clear();

    // draw the current demo method
    if (Assembly.getProcessState() == "boot")
    {
        drawStartScreen();
    }
    else if (Assembly.getProcessState() == "reboot")
    {
        drawRebootScreen();
    }
    else if (Assembly.getProcessState() == "new")
    {
        drawAssemblyInfo();
    }
    else if (Assembly.getProcessState() == "started")
    {
        drawProgressScreen();
    }
    else if (Assembly.getProcessState() == "wlanOk")
    {
        drawWlanOkScreen();
    }
    else
    {
        demos[demoMode]();
    }
    // 

    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.drawString(128, 54, String(millis() / 100 % 10)); // bottom right
    //  The coordinates define the right end of the text
    // display.setTextAlignment(TEXT_ALIGN_RIGHT);
    // display.drawString(128, 0, String(millis()));   //top right
    //  write the buffer to the display
    display.display();

    if (millis() - timeSinceLastModeSwitch > DEMO_DURATION)
    {
        demoMode = (demoMode + 1) % demoLength;
        timeSinceLastModeSwitch = millis();
    }
    counter++;
}
