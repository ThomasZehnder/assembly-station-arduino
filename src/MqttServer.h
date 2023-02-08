void mqttSetup(void);
void mqttLoop(void);

void mqttPublishLong(const char* topic, long x);
void mqttPublishString(const char* topic, String s);

void mqttSubscribe (const char *topic);

bool mqttCheckTopic(const char *topic, const char *inTopic);
