#include <SPI.h>
#include "RF24.h"
RF24 myRadio (7, 8); // CE, CSN
byte addresses[][6] = {"3110"};
struct data {
  double kp = 1 ;
  double ki = 0 ;
  double kd = 0;
  int active = 0;
};
String ss;
typedef struct data dataType;
dataType data;
void setup() {
  // put your setup code here, to run once:
  initialize_radio();
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    data.kp = Serial.parseFloat();
    data.ki = Serial.parseFloat();
    data.kd = Serial.parseFloat();
    date.active = Serial.parseInt();
    while (Serial.available())Serial.read();
    myRadio.write(&data, sizeof(data));
  }

}
void initialize_radio() {
  while (!myRadio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
  }
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;
  myRadio.openWritingPipe( addresses[0]);
}
