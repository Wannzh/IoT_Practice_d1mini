#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Pin LED
#define LED_HIJAU D2
#define LED_MERAH D1

// WIFI CONFIG
const char *ssid = "isi nama wifi sendiri";
const char *password = "isi password wifi sendiri";

// MQTT CONFIG
const char *mqtt_servcer = "154.19.37.27";
const int mqtt_port = 1883;
const char *mqtt_user = "yudhi";
const char *mqtt_pass = "yudhi123";
const char *mqtt_topic = "esp8266/led";

WiFiClient espClient;
PubSubClient client(espClient);

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

  // Matikan semua LED saat awal
  digitalWrite(LED_HIJAU, LOW);
  digitalWrite(LED_MERAH, LOW);
}

void loop()
{
  // LED Hijau ON, Merah OFF
  digitalWrite(LED_HIJAU, HIGH);
  digitalWrite(LED_MERAH, LOW);
  delay(1000);

  // LED Hijau OFF, Merah ON
  digitalWrite(LED_HIJAU, LOW);
  digitalWrite(LED_MERAH, HIGH);
  delay(1000);
}

