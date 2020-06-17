#include <ESP8266WiFi.h>
#include <SPI.h>
#include "MFRC522.h"

/* wiring the MFRC522 to ESP8266 (ESP-12)
RST     = GPIO5
SDA(SS) = GPIO4 
MOSI    = GPIO13 // D7
MISO    = GPIO12 // D6
SCK     = GPIO14 // D5
GND     = GND
3.3V    = 3.3V
*/

#define RST_PIN  5  // RST-PIN für RC522 - RFID - SPI - Modul GPIO5 
#define SS_PIN  4  // SDA-PIN für RC522 - RFID - SPI - Modul GPIO4 

const char *ssid =  "Home";     // change according to your Network - cannot be longer than 32 characters!
const char *pass =  "ahmed@abir@6997"; // change according to your Network

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
  Serial.begin(115200);    // Initialize serial communications
  delay(250);
  Serial.println(F("Booting...."));
  
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
  // Show some details of the PICC (that is: the tag/card)
  //Serial.print(F("Card UID:"));
  //dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  rfidUidPrintDec();
  Serial.println();
}

// Helper routine to dump a byte array as hex values to Serial
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
//  Serial.print(mfrc522.uid.uidByte[i], HEX);  // print without spaces
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
// print UID to Serial as a decimal value
void rfidUidPrintDec()
{
  if(mfrc522.uid.size == 4)
  {
    Serial.println(mfrc522.uid.size);
    Serial.println("Card UID: (DEC) " + (String)rfidUidToDecimal());
  }
  else
  {
    Serial.println(mfrc522.uid.size);
    Serial.println("Card UID: (DEC) " + (String)rfidUidToDecimal1());
    //Serial.println(F("Error converting UID to decimal:"));
    //Serial.println(F("UID size more than 4 bytes"));
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
