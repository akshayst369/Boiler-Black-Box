#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "Certificates.h"
// ---------------- WiFi ----------------
const char* ssid = "Ak32";
const char* password = "123456890";

// ---------------- HiveMQ ----------------
const char* mqtt_server = "094819d2e9f64c24aad18cf71f8fbdc6.s1.eu.hivemq.cloud";   // e.g. xxxxx.s2.eu.hivemq.cloud
const int mqtt_port = 8883;
const char* mqtt_user = "Johnny";
const char* mqtt_pass = "Johnny123456";

// ---------------- Topic ----------------
// boiler/{state}/{district}/{company}/{boiler_id}/data
const char* topic = "boiler/TN/Chennai/TataSteel/B01/data";

// ---------------- Root CA ----------------
// HiveMQ public root certificate


WiFiClientSecure espClient;
PubSubClient client(espClient);

// -------- Simulated values --------
float temperature = 180.0;
float pressure = 6.0;
float flow = 10.0;

// ---------------- WiFi connect ----------------
void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

// ---------------- MQTT reconnect ----------------
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to HiveMQ...");
    if (client.connect("ESP32-Boiler", mqtt_user, mqtt_pass)) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

// ---------------- Setup ----------------
void setup() {
  Serial.begin(115200);
  setup_wifi();

  espClient.setInsecure();
  client.setServer(mqtt_server, mqtt_port);
}

// ---------------- Loop ----------------
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // -------- Simulate sensor drift --------
  temperature += random(-5, 5) * 0.1;
  pressure += random(-3, 3) * 0.1;
  flow += random(-4, 4) * 0.1;

  unsigned long timestamp = millis();

  // -------- JSON payload --------
  String payload = "{";
  payload += "\"state\":\"TN\",";
  payload += "\"district\":\"Chennai\",";
  payload += "\"company\":\"TataSteel\",";
  payload += "\"boiler_id\":\"B01\",";
  payload += "\"temperature\":" + String(temperature, 2) + ",";
  payload += "\"pressure\":" + String(pressure, 2) + ",";
  payload += "\"flow\":" + String(flow, 2) + ",";
  payload += "\"timestamp\":" + String(timestamp);
  payload += "}";

  client.publish(topic, payload.c_str());

  Serial.println("Published:");
  Serial.println(payload);
  Serial.println("--------------------");

  delay(5000);   // send every 5 seconds
}
