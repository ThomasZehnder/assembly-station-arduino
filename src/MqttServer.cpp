#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <AsyncMqttClient.h>

#include "credentials.h"

#include "Global.h"

#include "MqttServer.h"
#include "dictionary.h"

AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;

String mqttHost;

Dictionary<String, String> SubscriptionList;

#define ASSENMBLY_JOB_TOPIC "job"

void connectToMqtt()
{
  Serial.println("MqttSetup (CallBack) --> Connecting to MQTT..." + mqttHost);
  mqttClient.connect();
}

void onWifiConnect(const WiFiEventStationModeGotIP &event)
{
  Serial.println("MqttSetup (CallBack) --> Connected to WiFi... " + WiFi.SSID());
  Serial.print("MqttSetup (CallBack)  --> IP address: ");
  Serial.println(WiFi.localIP());
  Assembly.wifiConnected = true;
  Assembly.localIp = WiFi.localIP().toString();
  Assembly.ssid = WiFi.SSID();
  Assembly.wlanConnectedProcess();

  // select mqtt server dependend to found Wifi
  byte cfgIndex = 0;
  for (cfgIndex = 0; cfgIndex < (sizeof(Assembly.cfg.wifi) / sizeof(Assembly.cfg.wifi[0])); cfgIndex++)
  {
    if (WiFi.SSID() == Assembly.cfg.wifi[cfgIndex].ssid)
    {

      mqttHost = Assembly.cfg.wifi[cfgIndex].ssid;
      mqttHost += "-";
      mqttHost += Assembly.cfg.mqtt[cfgIndex].host;

      IPAddress ip;
      if (ip.fromString(Assembly.cfg.mqtt[cfgIndex].host))
      {
        Serial.print("MqttSetup (CallBack) --> MQTT host: ");
        Serial.println(ip.toString());
      }
      else
      {
        Serial.print("MqttSetup (CallBack) --> error unusable IP: ");
        Serial.println(Assembly.cfg.mqtt[cfgIndex].host);
      }

      Assembly.mqttBroker = ip.toString();

      mqttClient.setServer(ip, Assembly.cfg.mqtt[cfgIndex].port);

      // check credentials
      if (strlen(Assembly.cfg.mqtt[cfgIndex].login) > 0)
      {
        Serial.print("MqttSetup (CallBack) --> use credentials!!!! : ");
        Serial.print(Assembly.cfg.mqtt[cfgIndex].login);
        Serial.print(" / ");
        Serial.println(Assembly.cfg.mqtt[cfgIndex].pw);
        mqttClient.setCredentials(Assembly.cfg.mqtt[cfgIndex].login, Assembly.cfg.mqtt[cfgIndex].pw);
      }

      break;
    }
  }

  Serial.print("MqttSetup (CallBack) --> mqtt client id: ");
  Serial.println(mqttClient.getClientId());

  connectToMqtt();
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected &event)
{
  Serial.println("MqttSetup (CallBack) --> Disconnected from WiFi." + mqttHost);
  Assembly.wifiConnected = false;
  mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
  // wifiReconnectTimer.once(2, connectToWifi);
}

void onMqttConnect(bool sessionPresent)
{
  Serial.println("MqttSetup (CallBack) --> Connected to MQTT.");
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

  mqttPublishString("myIpAddr", Assembly.localIp);
  mqttPublishString("compileDate", Assembly.compileDate);
  mqttPublishString("processState", Assembly.getProcessState());

  // subscribe assembly "job"
  mqttSubscribe(ASSENMBLY_JOB_TOPIC);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  Serial.println("MqttSetup (CallBack) --> Disconnected from MQTT.");
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
  Serial.print("  payload: ");
  Serial.println(payload);
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

  char s[255];
  memset(s, 0, sizeof(s));
  size_t l = len;
  if (len > sizeof(s) - 1)
  {
    l = sizeof(s) - 1;
  }
  memcpy(s, payload, l);

  // set received topic to list
  SubscriptionList.set(topic, String(s));

  // check on job, fixe defined
  if (mqttCheckTopic(ASSENMBLY_JOB_TOPIC, topic))
  {
    Assembly.newProcess(s);
  }
}

void onMqttPublish(uint16_t packetId)
{
  Serial.println("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void mqttSubscribe(const char *topic)
{
  String t(Assembly.deviceId);
  t += "/";
  t += topic;

  //uint16_t packetIdSub = mqttClient.subscribe(t.c_str(), 0);

  // check is subscription still done
  if (SubscriptionList.get(t) == "ndef")
  {

    uint16_t packetIdSub = mqttClient.subscribe(t.c_str(), 0);

    // add to list
    SubscriptionList.set(t, "new...");

    Serial.print("Add to list: Subscribing at QoS 2, packetId: ");
    Serial.print(packetIdSub);
    Serial.print(" topic: ");
    Serial.println(t);
  }

}

bool mqttCheckTopic(const char *topic, const char *inTopic)
{
  String t(Assembly.deviceId);
  t += "/";
  t += topic;
  return (strcmp(t.c_str(), inTopic) == 0);
}

void mqttPublishLong(const char *topic, long x)
{
  char s[200];
  ltoa(x, s, 10);
  String t(Assembly.deviceId);
  t += "/";
  t += topic;
  mqttClient.publish(t.c_str(), 0, true, s);
  //add to local list (only for test)
  //SubscriptionList.set(t,s);

  // Serial.println("Publishing long at QoS 0");
  // Serial.print(topic);
  // Serial.print(" : ");
  // Serial.println(x);
}
void mqttPublishString(const char *topic, String s)
{
  String t(Assembly.deviceId);
  t += "/";
  t += topic;
  mqttClient.publish(t.c_str(), 0, true, s.c_str());
  //add to local list (only for test)
  //SubscriptionList.set(t,s);

  // Serial.println("Publishing String at QoS 0");
  // Serial.print(topic);
  // Serial.print(" : ");
  // Serial.println(s);
}

// get value as String of subscripted value
String mqttGetSubscribeValue(const char *topic)
{
  // search value in topic list
  String t(Assembly.deviceId);
  t += "/";
  t += topic;
  String value = SubscriptionList.get(t);

  //Serial.print("mqttGetTopic ");
  //Serial.print(topic);
  //Serial.print(" : ");
  //Serial.println(value);

  return value;
}

void mqttClear(void)
{
  Serial.println("mqttClear()");
  SubscriptionList.clear();
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