#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "WIFI_USERNAME";
const char* password = "WIFI_PASSWORD";
const char* mqtt_server = "IP_BROKER"; //IP JETSON NANO (SERVER)
const int mqtt_port = 1883;
const char* mqtt_username = "MQTTBROKER_USERNAME";
const char* mqtt_password = "MQTTBROKER_PASSWORD";
const char* topic_pub = "sensor/data";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  // float sensor_value = analogRead(33); // Baca nilai sensor analog
  char msg[50];
  // sprintf(msg, "%f", sensor_value); // Konversi nilai sensor menjadi string
  sprintf(msg, "HELLO FROM ESP"); // Konversi nilai sensor menjadi string
  client.publish(topic_pub, msg); // Kirim data ke topik MQTT
  delay(5000); // Delay sebelum membaca sensor lagi
}
