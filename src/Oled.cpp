
// Include the correct display library

// For a connection via I2C using the Arduino Wire include:
#include <Wire.h>        // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" // legacy: #include "SSD1306.h"

// Initialize the OLED display using Arduino Wire:
SSD1306Wire display(0x3c, SDA, SCL); // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h e.g. https://github.com/esp8266/Arduino/blob/master/variants/nodemcu/pins_arduino.h

#include "Oled.h"

//start pixel of blue area
#define Y_OFFSET 16

#define DEMO_DURATION 3000
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 1;

void oledSetup()
{

    Serial.println("OledSetup --> Start");

    // Initialising the UI will init the display too.
    display.init();

    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);

    Serial.println("OledSetup --> End");
}

void drawFontFaceDemo()
{
    // Font Demo1
    // create more fonts at http://oleddisplay.squix.ch/
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Hello world");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, Y_OFFSET, "Hello world");
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 10+Y_OFFSET, "Hello world");
}

void drawTextFlowDemo()
{
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawStringMaxWidth(0, Y_OFFSET, 128,
                               "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore.");
}

void drawTextAlignmentDemo()
{
    // Text alignment demo
    display.setFont(ArialMT_Plain_10);

    // The coordinates define the left starting point of the text
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, Y_OFFSET, "Left aligned (0,Y_OFFSET)");

    // The coordinates define the center of the text
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 12+Y_OFFSET, "Center aligned (64,22)");

    // The coordinates define the right end of the text
    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.drawString(128, 33, "Right aligned (128,33)");
}

void drawRectDemo()
{
    // Draw a line horizontally
    display.drawHorizontalLine(0, Y_OFFSET-1, 128);  //last yellow
    //display.drawHorizontalLine(20, Y_OFFSET, 20);   //first blue
    //display.drawHorizontalLine(40, Y_OFFSET+1, 20);
    
    // Draw a pixel at given position
    for (int i = 0; i < 10; i++)
    {
        display.setPixel(i, i);
        display.setPixel(10 - i, i);
    }
    display.drawRect(12, 12, 20, 20);

    // Fill the rectangle
    display.fillRect(14, 14, 17, 17);

    // Draw a line horizontally
    display.drawHorizontalLine(0, 40, 20);

    // Draw a line horizontally
    display.drawVerticalLine(40, 0, 20);
}


void drawProgressBarDemo()
{
    int progress = (counter / 5) % 100;
    // draw the progress bar
    display.drawProgressBar(0, 32, 120, 10, progress);

    // draw the percentage as String
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 15, String(progress) + "%");
}

Demo demos[] = {drawFontFaceDemo, drawTextFlowDemo, drawTextAlignmentDemo, drawRectDemo, drawProgressBarDemo};
int demoLength = (sizeof(demos) / sizeof(Demo));
long timeSinceLastModeSwitch = 0;

void oledLoop()
{
    // clear the display
    display.clear();
    // draw the current demo method
    demos[demoMode]();

    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.drawString(128, 54, String(millis())); //bottom right
    // The coordinates define the right end of the text
    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.drawString(128, 0, String(millis()));   //top right
    // write the buffer to the display
    display.display();

    if (millis() - timeSinceLastModeSwitch > DEMO_DURATION)
    {
        demoMode = (demoMode + 1) % demoLength;
        timeSinceLastModeSwitch = millis();
    }
    counter++;
    delay(10);
}
