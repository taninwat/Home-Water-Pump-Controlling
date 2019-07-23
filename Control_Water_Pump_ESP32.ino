#include <WiFi.h> //https://www.arduino.cc/en/Reference/WiFi

#define WIFI_NAME "TVS_3BB 2.4G"
#define WIFI_PASS "0955167824"

#define WATER_PUMP_PIN 23

WiFiServer server(11008);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_STA);
    Serial.println("Attempting to connect to SSID: ");
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(WIFI_NAME, WIFI_PASS);
      for (int i = 0; i < 10; i++) {
        Serial.print(".");
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(500);
      }
    }
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
  }

  WiFiClient client = server.available();

  if (client) {
    if (client.connected()) {
      Serial.println("Client Connected");
      Serial.println("Turn On");
      digitalWrite(WATER_PUMP_PIN, HIGH);
      digitalWrite(LED_BUILTIN, HIGH);

      while (client.connected()) {
        Serial.println("Turn On Loop");
        Serial.println("Sending 100");
        server.write(100);
        Serial.print("Receiving ");
        Serial.println(client.read());
        delay(5000);
        if (client.read() < 0) {
          Serial.println(client.read());
          break;
        }
      }
    }
  }

  digitalWrite(WATER_PUMP_PIN, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("TURN OFF");
  delay(5000);
}
