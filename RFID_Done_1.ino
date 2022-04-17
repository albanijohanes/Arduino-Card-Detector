#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define LED_G 5 //define green LED pin
#define LED_R 4 //define red LED
#define buzzer 2 //buzzer pin
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myServo; //define servo name
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo.attach(3); //servo pin
  myServo.write(0); //servo start position
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(buzzer, OUTPUT);
  noTone(buzzer);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("Masukkan Kartu/KTP anda :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "75 5D 8A AC" || content.substring(1) == "05 87 84 64 56 A1 00") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Akses diterima");
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
    tone(buzzer, 10000);
    delay(100);
    noTone(buzzer);
    myServo.write(180);
    delay(7000);
    myServo.write(0);
    digitalWrite(LED_G, LOW);
  }
 
 else{
    Serial.println(" Akses ditolak");
    digitalWrite(LED_R, HIGH);
    tone(buzzer, 20000);
    delay(4000);
    digitalWrite(LED_R, LOW);
    noTone(buzzer);
  }
}
