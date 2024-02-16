#include <SPI.h>
#include "RF24.h"
RF24 myRadio (9, 10);
byte addresses[][6] = {"3110"};
struct data {
  double kp = 1 ;
  double ki = 0 ;
  double kd = 0;
  int active = 0;
};
typedef struct data dataType;
dataType data;
void initializeRadio() {
  while (!myRadio.begin())
    Serial.println(F("radio hardware is not responding!!"));
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}
void tuneValues(double *kp, double *ki, double *kd, int *active) {
  while (myRadio.available())
  {
    myRadio.read(&data, sizeof(data));
    *kp = data.kp;
    *ki = data.ki;
    *kd = data.kd;
    *active = data.active;
    Serial.println("kp : " + String(data.kp) + " ki : " + String(data.ki) + " kd : " + String(data.kd));
  }
}
