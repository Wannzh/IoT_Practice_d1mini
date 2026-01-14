#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Pin LED
#define LED_HIJAU D2
#define LED_MERAH D1

// WIFI CONFIG
const char *ssid = "awann";
const char *password = "hayoloapa";

// MQTT CONFIG
const char *mqtt_server = "154.19.37.27";
const int mqtt_port = 1883;
const char *mqtt_user = "yudhi";
const char *mqtt_pass = "yudhi123";
const char *mqtt_topic = "esp8266/led";

WiFiClient espClient;
PubSubClient client(espClient);

String clientId;

void mqttCallback(char *topic, byte *payload, unsigned int length);

void setupWiFi()
{
  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nWiFi connected");
}

void setup()
{
  Serial.begin(115200);

  pinMode(LED_HIJAU, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);

  setupWiFi();

  clientId = "D1Mini-" + String(ESP.getChipId());

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);

  // Matikan semua LED saat awal
  digitalWrite(LED_HIJAU, LOW);
  digitalWrite(LED_MERAH, LOW);
}

void mqttCallback(char *topic, byte *payload, unsigned int length)
{
  String message;

  for (unsigned int i = 0; i < length; i++)
  {
    message += (char)payload[i];
  }

  message.trim();

  Serial.println("MQTT x [" + String(topic) + "] => " + message);

  if (message == "ON Hijau")
  {
    Serial.println("Hijau Masuk");
    digitalWrite(LED_HIJAU, HIGH);
    digitalWrite(LED_MERAH, LOW);
  }
  else if (message == "ON Merah")
  {
    digitalWrite(LED_HIJAU, LOW);
    digitalWrite(LED_MERAH, HIGH);
  }
}

void reconnectMQTT()
{
  while (!client.connected())
  {
    Serial.print("Connecting MQTT... ");

    if (client.connect(
            clientId.c_str(),
            mqtt_user,
            mqtt_pass))
    {

      Serial.println("CONNECTED");
      client.subscribe(mqtt_topic);

      // Kirim status ke cloud
      client.publish("esp8266/status", "ONLINE");
    }
    else
    {
      Serial.print("FAILED, rc=");
      Serial.print(client.state());
      delay(3000);
    }
  }
}

void loop()
{
   if (!client.connected()) {
    reconnectMQTT();
  }

  client.loop();
}
