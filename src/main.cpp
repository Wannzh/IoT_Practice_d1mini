#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Pin LED
#define LED_HIJAU D2
#define LED_MERAH D1

// WIFI CONFIG
const char *ssid = "ssid wifi sendiri";
const char *password = "password wifi sendiri";

// MQTT CONFIG
const char *mqtt_server = "server mqtt";
const int mqtt_port = 0000; // port mqtt
const char *mqtt_user = "username mqtt";
const char *mqtt_pass = "password mqtt";

const char *TOPIC_CONTROL = "esp8266/led";
const char *TOPIC_STATUS = "esp8266/status";
const char *TOPIC_STATE = "esp8266/state";

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

  // Matikan semua LED saat awal
  digitalWrite(LED_HIJAU, LOW);
  digitalWrite(LED_MERAH, LOW);

  setupWiFi();

  clientId = "D1Mini-" + String(ESP.getChipId());

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);
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

  // Led Controll

  if (message == "ON Hijau")
  {
    digitalWrite(LED_HIJAU, HIGH);
    digitalWrite(LED_MERAH, LOW);
    client.publish(TOPIC_STATE, "HIJAU_ON", true);
  }
  else if (message == "ON Merah")
  {
    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(LED_HIJAU, LOW);
    client.publish(TOPIC_STATE, "MERAH_ON", true);
  }
  else if (message == "OFF ALL")
  {
    digitalWrite(LED_HIJAU, LOW);
    digitalWrite(LED_MERAH, LOW);
    client.publish(TOPIC_STATE, "ALL_OFF", true);
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
            mqtt_pass,
            "esp8266/status",
            1,
            true,
            "OFFLINE"))
    {
      Serial.println("CONNECTED");

      client.subscribe(TOPIC_CONTROL);

      // STATUS ONLINE (RETAIN)
      client.publish("esp8266/status", "ONLINE", true);
      client.publish(TOPIC_STATE, "ALL_OFF", true);
    }
    else
    {
      Serial.print("FAILED rc=");
      Serial.println(client.state());
      delay(3000);
    }
  }
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    setupWiFi();
  }

  if (!client.connected())
  {
    reconnectMQTT();
  }

  client.loop();
}
