#include <SPI.h>
#include "RF24.h"
RF24 myRadio (7, 8); // CE, CSN
byte addresses[][6] = {"3110"};
struct data {
  double x = 0 ;
  double y = 0 ;
  double z = 0;
};
String ss;
typedef struct data dataType;
dataType data;

void setup() {
  // put your setup code here, to run once:
  initializeRadio();
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (myRadio.available())
  {
    myRadio.read(&data, sizeof(data));
    Serial.println("@"+String(data.x)+" "+String(data.y)+" "+String(data.z)+"#");
  }
  
}
void initializeRadio() {
  while (!myRadio.begin())
    Serial.println(F("radio hardware is not responding!!"));
  Serial.println("hi"); 
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}
