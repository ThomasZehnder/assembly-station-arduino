void mqttSetup(void);
void mqttLoop(void);

void mqttPublishLong(const char* topic, long x);
void mqttPublishString(const char* topic, String s);