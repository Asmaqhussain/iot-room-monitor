#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 15
#define DHTTYPE DHT22
#define GAS_PIN 34

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  
  client.setServer(mqtt_server, mqtt_port);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32_Room_Sensor")) {
      Serial.println("connected!");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(3000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float temp = dht.readTemperature();
  int rawGas = analogRead(GAS_PIN);
  float airQuality = map(rawGas, 0, 4095, 100, 800);

  if (!isnan(temp)) {
    char payload[64];
    snprintf(payload, sizeof(payload), "{\"temp\": %.1f, \"air_quality\": %.1f}", temp, airQuality);
    
    client.publish("asmaq/iot/room/environment", payload);
    Serial.print("Published: ");
    Serial.println(payload);
  }
  
  delay(3000);
}
