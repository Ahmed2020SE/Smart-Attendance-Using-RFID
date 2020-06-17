#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "MFRC522.h"

LiquidCrystal_I2C lcd(0x27,20,4);

#define RST_PIN  5  // RST-PIN für RC522 - RFID - SPI - Modul GPIO5 
#define SS_PIN  4  // SDA-PIN für RC522 - RFID - SPI - Modul GPIO4 
const char *ssid =  "home 2";     // change according to your Network - cannot be longer than 32 characters!
const char *pass =  "ahmed@abir@6997"; // change according to your Network
String db_id;
String read_id;
String sid;
const char* host = "192.168.43.14";

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
  Serial.begin(115200);    // Initialize serial communications
  delay(250);
  Serial.println(F("Booting...."));
  Wire.begin(2,0);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Welcome To AAST");
  lcd.setCursor(3,1);
  lcd.print("Scan your ID");
  SPI.begin();           // Init SPI bus
  mfrc522.PCD_Init();    // Init MFRC522
  
  WiFi.begin(ssid, pass);
  
  int retries = 0;
  while ((WiFi.status() != WL_CONNECTED) && (retries < 10)) {
    retries++;
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("WiFi connected"));
  }
  
  Serial.println(F("Ready!"));
  Serial.println(F("======================================================")); 
  Serial.println(F("Scan for Card and print UID:"));

}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    delay(50);
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }
  read_id=(String)rfidUidPrintDec();
  delay(500);
  WiFiClient client; 
  
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) { //works!
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String writeURL = "/update.php";
  String url = "/reader.php";
  String idURL="/ID.php";
  
  url += "?card_id="+read_id;
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
   while (client.connected())
    {
      if (client.available())
      {
        /*reading From Client*/
       String line = client.readStringUntil('\n');
       db_id=line;
        }
        else
        {
          Serial.print(".");
        }
      }
      Serial.println();
      client.stop();
      if (!client.connect(host, httpPort)) { //works!
    Serial.println("connection failed");
    return;
  }
    if(db_id.equals(read_id)){
      idURL += "?card_id="+read_id;
      client.print(String("GET ") + idURL + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
       while (client.connected())
    {
      if (client.available())
      {
        /*reading From Client*/
       String line2 = client.readStringUntil('\n');
       sid=line2;
        Serial.println(line2);
        }
        else
        {
          Serial.print(".");
        }
     }
        Serial.println();
     }
     client.stop();
     if (!client.connect(host, httpPort)) { //works!
      Serial.println("connection failed");
      return;
      }
   // We now create a URI for the request
      if(db_id.equals(read_id)){
      writeURL += "?card_id="+read_id;
      client.print(String("GET ") + writeURL + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
       while (client.connected())
    {
      if (client.available())
      {
        /*reading From Client*/
       String line1 = client.readStringUntil('\n');
       int updateIndex=line1.indexOf("Update Success");
       String updateS=line1.substring(updateIndex);
        if(updateS.equals("Update Success")){
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("ID: "+sid);
        lcd.setCursor(1,1);
        lcd.print("Attend Success");
        delay(15000);
        lcd_home();
        }
        Serial.println(line1);
        }
        else
        {
          Serial.print(".");
        }
     }
     Serial.println();
     client.stop();
      }
      Serial.print("Database: ");
      Serial.println(db_id);
      Serial.print("Read: ");
      Serial.println(read_id);
}
unsigned long rfidUidPrintDec()
{
  if(mfrc522.uid.size == 4)
  {
    
    return rfidUidToDecimal();
  }
  else
  {
    return rfidUidToDecimal1();
  }
}
// convert 4 bytes long UID to a decimal value
unsigned long rfidUidToDecimal()
{
  return  (unsigned long) mfrc522.uid.uidByte[0] << 24 |
      (unsigned long) mfrc522.uid.uidByte[1] << 16 |
      (unsigned long) mfrc522.uid.uidByte[2] << 8  |
      (unsigned long) mfrc522.uid.uidByte[3];
}
// convert 7 bytes long UID to a decimal value(Our Card ID)
unsigned long rfidUidToDecimal1()
{
  return  (unsigned long) mfrc522.uid.uidByte[0] << 48 |
      (unsigned long) mfrc522.uid.uidByte[1] << 40 |
      (unsigned long) mfrc522.uid.uidByte[2] << 32  |
      (unsigned long) mfrc522.uid.uidByte[3] << 24  |
      (unsigned long) mfrc522.uid.uidByte[4] << 16  |
      (unsigned long) mfrc522.uid.uidByte[5] << 8  |
      (unsigned long) mfrc522.uid.uidByte[6];
}
void lcd_home(){
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Welcome To AAST");
  lcd.setCursor(3,1);
  lcd.print("Scan your ID");
}
