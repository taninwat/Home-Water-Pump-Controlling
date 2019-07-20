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
  pinMode(WATER_SENSOR_PIN, INPUT);
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
  Serial.print("Signal = ");
  Serial.println(digitalRead(WATER_SENSOR_PIN));

  WiFiClient client;

  if (digitalRead(WATER_SENSOR_PIN) == HIGH) {
    Serial.println("Confirming");
    for (int i = 0; i < 10; i++) {
      Serial.print("Countdown ");
      Serial.print(i);
      Serial.println(" Sec");
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      delay(1000);
      if (digitalRead(WATER_SENSOR_PIN) == LOW) {
        break;
      }
    }
    Serial.println("Connecting to the server");
    client.connect("192.168.1.19", 11008);
    Serial.println("Signal On");
    digitalWrite(LED_BUILTIN, HIGH);
    while (digitalRead(WATER_SENSOR_PIN) == HIGH) {
      if (digitalRead(WATER_SENSOR_PIN) == LOW) {
        break;
      }
      /*
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
      */
      Serial.println("Signal On Loop");
      delay(5000);
    }
  }

  if (digitalRead(WATER_SENSOR_PIN) == LOW) {
    Serial.println("Signal Off");
    client.stop();
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Disconnected");
    /*
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
    */
    delay(1000);
  }
}
