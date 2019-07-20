#include <WiFi.h> //https://www.arduino.cc/en/Reference/WiFi

#define WIFI_NAME "TVS_3BB 2.4G"
#define WIFI_PASS "0955167824"

#define WATER_PUMP_PIN 23

String apiKey = "0LP32ZK1T6SWYCJM";
const char* thingspeakserver = "api.thingspeak.com";

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
      Serial.println(".");
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      delay(5000);
    }
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
  }

  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client Connected");
    while (client) {
      Serial.println("Turn On");
      digitalWrite(WATER_PUMP_PIN, HIGH);
      digitalWrite(LED_BUILTIN, HIGH);

      if (client.connect(thingspeakserver, 80)) {
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
      }
      delay(1000);
    }
  }
  digitalWrite(WATER_PUMP_PIN, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("TURN OFF");
  if (client.connect(thingspeakserver, 80)) {
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
  }
  delay(1000);

}
