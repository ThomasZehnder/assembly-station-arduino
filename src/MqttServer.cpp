#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <AsyncMqttClient.h>

#include "credentials.h"

#include "Global.h"

#include "MqttServer.h"
// #define WIFI_SSID "..."
// #define WIFI_PASSWORD "...."

// 192.168.1.95
// #define MQTT_HOST IPAddress(192, 168, 1, 95)
// #define MQTT_PORT 1883

AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;

String mqttHost;

#define ASSENMBLY_JOB_TOPIC "assembly-001/job"

void connectToMqtt()
{
  Serial.println("MqttSetup --> Connecting to MQTT..." + mqttHost);
  mqttClient.connect();
}

void onWifiConnect(const WiFiEventStationModeGotIP &event)
{
  Serial.println("MqttSetup --> Connected to Wi-Fi.");
  Assembly.wifiConnected = true;

  // get config in dependecy of connected WLAN
  if (WiFi.SSID() == WIFI_SSID_1)
  {
    Serial.println(WIFI_SSID_1);
    mqttHost = WIFI_SSID_1;
    mqttHost += "-" + MQTT_HOST_1.toString();
    mqttClient.setServer(MQTT_HOST_1, MQTT_PORT_1); // see  credentials.h
  }
  else
  {
    Serial.println(WIFI_SSID);
    mqttHost = WIFI_SSID;
    mqttHost += "-" + MQTT_HOST.toString();
    mqttClient.setServer(MQTT_HOST, MQTT_PORT); // see  credentials.h
  }

  connectToMqtt();
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected &event)
{
  Serial.println("MqttSetup --> Disconnected from Wi-Fi." + mqttHost);
  Assembly.wifiConnected = false;
  mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
  // wifiReconnectTimer.once(2, connectToWifi);
}

void onMqttConnect(bool sessionPresent)
{
  Serial.println("Connected to MQTT.");
  Assembly.mqttConnected = true;
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
  /*   uint16_t packetIdSub = mqttClient.subscribe("test/lol", 2);
    Serial.print("Subscribing at QoS 2, packetId: ");
    Serial.println(packetIdSub);
    mqttClient.publish("test/lol", 0, true, "test 1");
    Serial.println("Publishing at QoS 0");
    uint16_t packetIdPub1 = mqttClient.publish("test/lol", 1, true, "test 2");
    Serial.print("Publishing at QoS 1, packetId: ");
    Serial.println(packetIdPub1);
    uint16_t packetIdPub2 = mqttClient.publish("test/lol", 2, true, "test 3");
    Serial.print("Publishing at QoS 2, packetId: ");
    Serial.println(packetIdPub2); */

  mqttPublishString("assembly-001/myIpAddr", Assembly.localIp);
  mqttPublishString("assembly-001/processState", Assembly.getProcessState());

  // subscribe assembly job
  uint16_t packetIdSub = mqttClient.subscribe(ASSENMBLY_JOB_TOPIC, 2);
  Serial.print("Subscribing at QoS 2, packetId: ");
  Serial.println(packetIdSub);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  Serial.println("Disconnected from MQTT.");
  Assembly.mqttConnected = false;

  if (WiFi.isConnected())
  {
    mqttReconnectTimer.once(2, connectToMqtt);
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos)
{
  Serial.println("Subscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.print("  qos: ");
  Serial.println(qos);
}

void onMqttUnsubscribe(uint16_t packetId)
{
  Serial.println("Unsubscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  Serial.println("Publish received.");
  Serial.print("  topic: ");
  Serial.println(topic);
  Serial.print("  qos: ");
  Serial.println(properties.qos);
  Serial.print("  dup: ");
  Serial.println(properties.dup);
  Serial.print("  retain: ");
  Serial.println(properties.retain);
  Serial.print("  len: ");
  Serial.println(len);
  Serial.print("  index: ");
  Serial.println(index);
  Serial.print("  total: ");
  Serial.println(total);

  if (strcmp(topic, ASSENMBLY_JOB_TOPIC) == 0)
  {
    Assembly.newProcess();
  }
}

void onMqttPublish(uint16_t packetId)
{
  Serial.println("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void mqttPublishLong(const char *topic, long x)
{
  char s[200];
  ltoa(x, s, 10);
  mqttClient.publish(topic, 0, true, s);
  // Serial.println("Publishing long at QoS 0");
  // Serial.print(topic);
  // Serial.print(" : ");
  // Serial.println(x);
}
void mqttPublishString(const char *topic, String s)
{
  mqttClient.publish(topic, 0, true, s.c_str());
  // Serial.println("Publishing String at QoS 0");
  // Serial.print(topic);
  // Serial.print(" : ");
  // Serial.println(s);
}
void mqttSetup()
{

  Serial.println("MqttSetup --> Start");

  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  // wait until WLAN is recogniced to set MQTT server configuration
  // mqttClient.setServer(MQTT_HOST, MQTT_PORT);  //see  credentials.h

  Serial.println("MqttSetup --> End");
}

void mqttLoop()
{
  // nothing, all "event based"
}