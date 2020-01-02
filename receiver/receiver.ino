/*********
  Modified from the examples of the Arduino LoRa library
  More resources: https://randomnerdtutorials.com
  src: https://randomnerdtutorials.com/esp32-lora-rfm95-transceiver-arduino-ide/
*********/

#include <math.h>
#include <SPI.h>
#include <LoRa.h>

float rssi;
float rssi_db;
float pwr;
int percent;

//define the pins used by the transceiver module
#define ss 10
#define rst A1
#define dio0 4

void setup() {
  //initialize Serial Monitor
  Serial.begin(57600);
  pinMode(A5,OUTPUT);
  while (!Serial);
  Serial.println("LoRa Receiver");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(921E6)) {
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
//    Serial.print("No: '");
//    Serial.print("\t");

    // read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData); Serial.print("\t"); 
      
    if(LoRaData == "1"){
      digitalWrite(A5,HIGH);
    
    }

    else{
      digitalWrite(A5,LOW);
    }  
    }

}
}
