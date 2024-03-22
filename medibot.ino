#include <RFID.h>
#include <SPI.h>
#include <PulseSensorPlayground.h>
const int OUTPUT_TYPE = SERIAL_PLOTTER;
#define SDA_DIO 9
#define RESET_DIO 8
RFID RC522(SDA_DIO,RESET_DIO);
int ir1,ir2;
const int PulseWire = A0;       
const int LED = LED_BUILTIN;    
int Threshold = 550; 
PulseSensorPlayground pulseSensor;
void setup() {
  Serial.begin(9600);
  SPI.begin(); // Corrected case for SPI
  RC522.init();
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(30,INPUT);
  pinMode(31,INPUT);
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED); 
  pulseSensor.setThreshold(Threshold);
}

void loop() {
  String tag="";
  if(RC522.isCard()){
    RC522.readCardSerial();
    for(int i=0;i<5;i++){
       tag+=String(RC522.serNum[i],DEC);
    }
    tag.toUpperCase();
    if(tag == "532091491112"){
      Serial.println("Card is Detected, lets start");
      ir1=digitalRead(31);
      ir2=digitalRead(30);
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
      
      else if(ir1==0 && ir2==1){
        digitalWrite(2,LOW);
        analogWrite(3,255);
        digitalWrite(4,HIGH);
        analogWrite(5,255);
        digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
        digitalWrite(23,LOW);
        digitalWrite(22,HIGH);   
      }
      
      else if(ir1==0 && ir2==1){
        digitalWrite(2,HIGH);
        analogWrite(3,255);
        digitalWrite(4,LOW);
        analogWrite(5,255);
        digitalWrite(6,LOW);
        digitalWrite(7,HIGH);
        digitalWrite(23,HIGH);
        digitalWrite(22,LOW);   
      }
      else if(ir1==0 && ir2==0 ){
        digitalWrite(2,LOW);
        analogWrite(3,0);
        digitalWrite(4,HIGH);
        analogWrite(5,0);
        digitalWrite(6,LOW);
        digitalWrite(7,LOW);
        digitalWrite(23,LOW);
        digitalWrite(22,LOW);   
      }
    }
    else if(tag=="191521382928"){
      
      Serial.println("Card is Detected, lets start bpm");
      if (pulseSensor.sawStartOfBeat()) { 
        int myBPM = pulseSensor.getBeatsPerMinute();
        Serial.println(myBPM);
      }
        delay(20);
    
  }
  }
}
