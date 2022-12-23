#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <ArduinoJson.h>

ESP8266WebServer server(80);

#define ACTIVITY_LED_PIN LED_BUILTIN

long triggerActivityTime = 0;

void triggerActivity()
{
  digitalWrite(ACTIVITY_LED_PIN, 0);
  triggerActivityTime = millis();
}

int httpRssi(void)
{
  return WiFi.RSSI();
}

void handleJson()
{
  triggerActivity();

  // see: https://arduinojson.org/

  // Allocate a temporary JsonDocument
  // Use https://arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<500> doc;

  doc["assembly"] = "001";
  doc["millis"] = millis();
  doc["rssi"] = httpRssi();

  // Create the "digital" array
  JsonArray digitalValues = doc.createNestedArray("digital");
  for (int pin = 0; pin < 17; pin++)
  {
    // Read the digital input
    int value = digitalRead(pin);

    // Add the value at the end of the array
    digitalValues.add(value);
    //digitalValues.add(pin);
    //digitalValues.add("pin");
  }

  Serial.print(F("Sending: "));
  serializeJson(doc, Serial);
  Serial.println();

  // Lastly, you can print the resulting JSON to a String
  String output;
  serializeJson(doc, output);
  server.send(200, "application/json", output);
}

void handleRoot()
{
  triggerActivity();
  server.send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound()
{
  triggerActivity();
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.println(message);
}

void httpSetup(void)
{

  Serial.println("HttpSetup --> Start");

  pinMode(ACTIVITY_LED_PIN, OUTPUT);
  digitalWrite(ACTIVITY_LED_PIN, 1);

  // WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, password);
  Serial.println("Wifi startet from MqttSetup() :-)");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("signal strength (RSSI):");
  Serial.println(WiFi.RSSI());

  Serial.println("HttSetup");

  server.on("/", handleRoot);
  server.on("/json", handleJson);

  server.on("/inline", []()
            { server.send(200, "text/plain", "this works as well"); });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  Serial.println("HttpSetup --> End");
}

void httpLoop(void)
{
  server.handleClient();
  
  if (triggerActivityTime != 0)
  {
    long actualMillis = millis();
    if (actualMillis - triggerActivityTime - 200 > 0)
    {
      digitalWrite(ACTIVITY_LED_PIN, 1);
      triggerActivityTime = 0;
    }
  }
}
