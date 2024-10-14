
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define RELAY_PIN 8

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin(); 
  rfid.PCD_Init(); 
  pinMode(RELAY_PIN, OUTPUT);
  Serial.println("Place your RFID card/tag to unlock");
      digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }
  
  Serial.print("UID tag: ");
  String content = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    content.concat(String(rfid.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println(content);

  if (content == "4A2AB17") {
    Serial.println("Access Granted");
    digitalWrite(RELAY_PIN, HIGH); 
    delay(5000); 
    digitalWrite(RELAY_PIN, LOW); 
  }

}
