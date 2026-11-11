#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "TEN_WIFI";
const char* pass = "MAT_KHAU";

const char* broker = "test.mosquitto.org";
const char* topic = "bcse/th3/nhom-Kud0_75";
const char* topicLed = "bcse/th3/nhom-Kud0_75/led";
const int LED = 2;

WiFiClient wifi;
PubSubClient mqtt(wifi);
String clientId;
int dem = 0;

void nhanTin(char* t, byte* payload, unsigned int len) {
  String msg;
  for (unsigned int i = 0; i < len; i++) msg += (char)payload[i];
  Serial.printf("Nhan [%s]: %s\n", t, msg.c_str());
  if (String(t) == topicLed) {
    if (msg == "1") { digitalWrite(LED, HIGH); Serial.println("LED -> BAT"); }
    else if (msg == "0") { digitalWrite(LED, LOW); Serial.println("LED -> TAT"); }
  }
}

void noiBroker() {
  while (!mqtt.connected()) {
    Serial.printf("Noi broker %s voi client id %s ... ", broker, clientId.c_str());
    if (mqtt.connect(clientId.c_str())) {
      Serial.println("OK");
      mqtt.subscribe(topicLed);
      Serial.printf("Da subscribe %s\n", topicLed);
    } else {
      Serial.printf("loi %d, thu lai sau 2 s\n", mqtt.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  WiFi.begin(ssid, pass);
  Serial.printf("Dang noi vao %s", ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nIP: ");
  Serial.println(WiFi.localIP());
  clientId = "esp32-Kud0_75-" + String((uint32_t)ESP.getEfuseMac(), HEX);
  mqtt.setServer(broker, 1883);
  mqtt.setCallback(nhanTin);
  noiBroker();
}

void loop() {
  if (!mqtt.connected()) noiBroker();
  mqtt.loop();
  static uint32_t tGui = 0;
  if (millis() - tGui >= 2000) {
    tGui = millis();
    mqtt.publish(topic, String(dem).c_str());
    Serial.printf("Publish [%s]: %d\n", topic, dem++);
  }
}