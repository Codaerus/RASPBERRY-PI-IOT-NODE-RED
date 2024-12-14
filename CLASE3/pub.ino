#include <PubSubClient.h>
#include <WiFi.h>

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  setup_wifi();
  client.setServer("192.168.1.14",1883);
}

void loop() {
  client.connect("ESP32");
  client.publish("canalx","hola desde esp32");
  delay(5000);
}

void setup_wifi(){
  Serial.begin(9600);
  WiFi.begin("MOVISTAR_78A8","NS2ajtQJ7TtDt9m"); //DHCP
  while(WiFi.status() != WL_CONNECTED)
    {
      delay(300);
      Serial.print(".");
    }
  Serial.println(WiFi.localIP());
}
