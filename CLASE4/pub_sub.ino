#include <PubSubClient.h>
#include <WiFi.h>

WiFiClient espClient;
PubSubClient client(espClient);
char msg[20];
unsigned long t = 0;
void setup() {
  setup_wifi();
  client.setServer("192.168.1.14",1883);
  client.setCallback(callback);
}

void callback(const char* topic, byte* payload, unsigned int length){
    payload[length] = '\0';
    String val = String((char*)payload);
    Serial.println(val);
}

void reconnect(){
  if(client.connect("ESP32")){
    Serial.println("MQTT OK");
    client.subscribe("canaly");
  }
}

void loop() {
  if(!client.connected()){
    reconnect();
  }
  client.loop();
  while(millis() - t >= 60000 ){
    int humedad = 82;
    int temperatura = 18;
    snprintf(msg,20,"%d,%d",humedad,temperatura);
    client.publish("canalx",msg);
    t = millis();
  }
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
