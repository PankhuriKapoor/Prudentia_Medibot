#include <MFRC522.h>
#include <SPI.h>
constexpr uint8_t RST_PIN = 9; // reset pin
constexpr uint8_t SS_PIN = 10;
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
String tag;
int ir1,ir2,ir3,ir4,ir5,ir6;
void setup() {
  Serial.begin(115200);
  spi.begin();
  rfid.PCD_Init();
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}

void loop() {
  if(!rfid.PICC_IsNewCardPresent())
    return;
  if(rfid.PICC_ReadCardSerial()){
    for(byte i=0;i<4;i++){
      tag+=rfid.uid.uidByte[i];
    }
    if(tag==' '){
      if(ir1==0 && ir2==0){
        digitalWrite(2,HIGH);
        analogWrite(3,255);
        digitalWrite(4,HIGH);
        analogWrite(5,255);
        digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
        digitalWrite(23,HIGH);
        digitalWrite(22,LOW);   
      }
      
      if(ir1==1 && ir2==0){
        digitalWrite(2,LOW);
        analogWrite(3,255);
        digitalWrite(4,HIGH);
        analogWrite(5,255);
        digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
        digitalWrite(23,LOW);
        digitalWrite(22,HIGH);   
      }
      
      if(ir1==1 && ir2==0){
        digitalWrite(2,HIGH);
        analogWrite(3,255);
        digitalWrite(4,LOW);
        analogWrite(5,255);
        digitalWrite(6,LOW);
        digitalWrite(7,HIGH);
        digitalWrite(23,HIGH);
        digitalWrite(22,LOW);   
      }
      if(ir1==0 && ir2==0 ){
        digitalWrite(2,LOW);
        analogWrite(3,255);
        digitalWrite(4,HIGH);
        analogWrite(5,255);
        digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
        digitalWrite(23,HIGH);
        digitalWrite(22,LOW);   
      }
    }
  }
  

}
