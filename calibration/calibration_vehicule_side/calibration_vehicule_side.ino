#include "mpu9250.h"
#include <SPI.h>
#include "RF24.h"
RF24 myRadio (7, 8); // CE, CSN
Mpu9250 imu(&Wire, 0x68);
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
  initializeMpu();
  initialize_radio();
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (imu.Read()) {
    data.x = imu.mag_x_ut();
    data.y = imu.mag_y_ut();
    data.z = imu.mag_z_ut();
    myRadio.write(&data, sizeof(data));
    Serial.println(data.x);
  }
  delay(80);

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
void initializeMpu() {
  if (!imu.Begin()) {
    Serial.println("IMU initialization unsuccessful");
    while (1) {}
  }
}
