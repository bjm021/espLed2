#include "WiFi.h"
#include "AsyncUDP.h"
const char* ssid = "SSID";
const char* pass = "PASS";

// UDP Handler
AsyncUDP udp;

// setting PWM properties
const int freq = 5000;
const int resolution = 8;

//current colot storage
int currentR = 0;
int currentG = 0;
int currentB = 0;
//int currentA = 0;
 
void setup()
{
  Serial.begin(115200);
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // configure LED PWM functionalitites
  ledcSetup(0, freq, resolution);
  ledcSetup(1, freq, resolution);
  ledcSetup(2, freq, resolution);
  ledcSetup(3, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(16, 0);
  ledcAttachPin(17, 1);
  ledcAttachPin(18, 2);
  ledcAttachPin(19, 3);
 
  if (udp.listen(65000)) {
    Serial.print("UDP running at IP: ");
    Serial.print(WiFi.localIP());
    Serial.println(" port: 65000");
    udp.onPacket([](AsyncUDPPacket packet) {
      String text = (const char*)packet.data();      
      if (text.startsWith("GET")) {
        packet.printf("%u;%u;%u", currentR, currentG, currentB);
      } else if (text.startsWith("R")) {
        Serial.println("Setting red to " + text.substring(1, 4));
        ledcWrite(0, text.substring(1, 4).toInt());
        currentR = text.substring(1, 4).toInt();
      } else if (text.startsWith("G")) {
        Serial.println("Setting green to " + text.substring(1));
        ledcWrite(1, text.substring(1, 4).toInt());
        currentG = text.substring(1, 4).toInt();
      } else if (text.startsWith("B")) {
        Serial.println("Setting blue to " + text.substring(1));
        ledcWrite(2, text.substring(1, 4).toInt());
        currentB = text.substring(1, 4).toInt();
      }
      //packet.printf("ESP32 received %u bytes of datas", packet.length()); //send what you received to sender via UDP
    });
  }
}
 
void loop()
{
  delay(1000); //if no delay, UDP message will not be loaded
}
