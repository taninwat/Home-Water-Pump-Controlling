#include <WiFi.h> //https://www.arduino.cc/en/Reference/WiFi

#define WIFI_NAME "TVS_3BB 2.4G"
#define WIFI_PASS "0955167824"

#define WATER_SENSOR_PIN 23

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(WATER_SENSOR_PIN, INPUT);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_STA);
    Serial.println("Attempting to connect to SSID: ");
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(WIFI_NAME, WIFI_PASS);
      Serial.println(".");
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      delay(5000);
    }
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  Serial.print("Signal = ");
  Serial.println(digitalRead(WATER_SENSOR_PIN));
  WiFiClient client;

  if (digitalRead(WATER_SENSOR_PIN) == HIGH) {
    Serial.println("Confirming");
    for (int i = 0; i < 10; i++) {
      Serial.println("Countdown ");
      Serial.print(i);
      Serial.println("Sec");
      delay(1000);
      if (digitalRead(WATER_SENSOR_PIN) == LOW) {
        break;
      }
    }
    if (digitalRead(WATER_SENSOR_PIN) == HIGH) {
      client.connect("192.168.1.19", 11008);
      Serial.println("Connected to the server");
      while (digitalRead(WATER_SENSOR_PIN) == HIGH) {
        Serial.println("Signal On");
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
      }
    }
  }

  else if (digitalRead(WATER_SENSOR_PIN) == LOW) {
    Serial.println("Signal Off");
    client.stop();
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Disconnected");
    delay(1000);
  }

}
