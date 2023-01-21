# assembly-station-arduino
IoT assembly station with arduino board

## Get from Git
    git clone https://github.com/ThomasZehnder/assembly-station-arduino.git

## Used Hardware ESP8266
The ESP8266 requires a 3.3V power supply. 
see https://randomnerdtutorials.com/vs-code-platformio-ide-esp32-esp8266-arduino/

![ESP8266 Pinout](/images/ESP-12E-Development-Board-ESP8266-NodeMCU-Pinout.png)

### Wirering
    // Secound Timer
    #define TOGGLE_LED_PIN D0 

    //D1 = SDL for OLED display
    //D2 = SDA for OLED display

    //D3 = WS2812 data line (LEDS need 5V, signal only 3.3V works)

    //D4 is reserved for build In led -> show http activity
    
    #define KEY1_PIN D7
    #define KEY2_PIN D6
    #define KEY3_PIN D5

## Use PlatformIO
In VSCode see elements in the buttom left corner to transfer projekt to arduino board.

## Use Filesysten

https://randomnerdtutorials.com/esp8266-nodemcu-vs-code-platformio-littlefs/

SPIFFS is currently deprecated and may be removed in future releases of the core.

Use LittleFS instead

### Uploading Filesystem Image
After creating and saving the file or files you want to upload under the data folder, follow the next steps:

* Click the PIO icon at the left side bar. The project tasks should open.
* Select env:nodemcuv2 (it may different depending on the board you’re using).
* Expand the Platform menu.
* Select Build Filesystem Image.
* Finally, click Upload Filesystem Image.

## configure Wifi and Webserver

https://tttapa.github.io/ESP8266/Chap12%20-%20Uploading%20to%20Server.html

Configure two WLAN, in case none is connected, ESP8266 will act as WLAN Hotspot. 

### Upload Files to ESP8266

e.g. for Updating configuration or other files.
http://192.168.1.157/upload


### Reboot Arduino by REST Call
http://192.168.1.157/reboot

### File Directory Arduino by REST Call
http://192.168.1.157/dir

## MQTT Connection
Try public internet accessible MQTT broker 


        "NAME": "public.mqtthq.com",
        "HOST": "52.13.116.147",
        "PORT": 1883,
        "LOGIN": "",
        "PASSWORD": ""

        "NAME": "public:public@public.cloud.shiftr.io 34.77.13.55",
        "HOST": "34.77.13.55",
        "PORT": 1883,
        "LOGIN": "public",
        "PASSWORD": "public"