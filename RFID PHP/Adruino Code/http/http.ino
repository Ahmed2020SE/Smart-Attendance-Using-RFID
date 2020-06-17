#include <ESP8266WiFi.h>
#include <SPI.h>
#include <ESP8266HTTPClient.h>
const char *ssid =  "Home";     // change according to your Network - cannot be longer than 32 characters!
const char *pass =  "ahmed@abir@6997"; // change according to your Network
void setup() {
    Serial.begin(115200);
    delay(250);
     Serial.println(F("Booting...."));
  SPI.begin();           // Init SPI bus
   WiFi.begin(ssid, pass);
  int retries = 0;
  while ((WiFi.status() != WL_CONNECTED) && (retries < 10)) {
    retries++;
    delay(300);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected");
  }
  Serial.println(F("Ready!"));
  Serial.println(F("======================================================")); 
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://192.168.1.5/reader.php?card_id=317086940");
  int httpcode=http.GET();
  String ID=http.getString();
  Serial.println(ID);
   http.end();
  }
 
  

}
String getValue(String data,char separator,int index){
  int found=0;
  int strIndex[]={0,0};
  int maxIndex=data.length()-1;
  
  }
