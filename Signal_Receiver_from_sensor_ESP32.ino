#include <WiFi.h> //https://www.arduino.cc/en/Reference/WiFi

#define WIFI_NAME "TVS_3BB 2.4G"
#define WIFI_PASS "0955167824"

#define WATER_SENSOR_PIN 23

String apiKey = "0LP32ZK1T6SWYCJM";
const char* thingspeakserver = "api.thingspeak.com";

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(WATER_SENSOR_PIN, INPUT_PULLDOWN);
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
  }

  WiFiClient client;

  if (digitalRead(WATER_SENSOR_PIN) == HIGH) {

    client.connect(thingspeakserver, 80);
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += HIGH;
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    Serial.println("Thingspeak Updated");

    Serial.println("Connecting to the server");
    client.connect("192.168.1.19", 11008);
    Serial.println("Signal On");
    digitalWrite(LED_BUILTIN, HIGH);

    while (digitalRead(WATER_SENSOR_PIN) == HIGH) {
      if (digitalRead(WATER_SENSOR_PIN) == LOW) {
        break;
      }
      Serial.println("Signal On Loop");
      Serial.println("Sending 255");
      client.write(255);
      Serial.print("Receiving ");
      Serial.println(client.read());
      delay(2500);
    }

    client.connect(thingspeakserver, 80);
    postStr = apiKey;
    postStr += "&field1=";
    postStr += HIGH;
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    Serial.println("Thingspeak Updated");

  }

  if (digitalRead(WATER_SENSOR_PIN) == LOW) {

    client.connect(thingspeakserver, 80);
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += LOW;
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    client.stop();

    while (digitalRead(WATER_SENSOR_PIN) == LOW) {
      if (digitalRead(WATER_SENSOR_PIN) == HIGH) {
        break;
      }
      Serial.println("Signal Off Loop");
      digitalWrite(LED_BUILTIN, LOW);
      delay(5000);
    }

    client.connect(thingspeakserver, 80);
    postStr = apiKey;
    postStr += "&field1=";
    postStr += LOW;
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    client.stop();

  }
}
