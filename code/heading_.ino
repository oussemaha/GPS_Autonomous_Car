#include "mpu9250.h"
#include "math.h"
Mpu9250 imu(&Wire, 0x68);
double A[3][3] = {
  {1.100587, -0.004432, 0.008248},
  { -0.004432, 1.084713, 0.064208},
  {0.008248, 0.064208, 1.132475}
};
double calibratedValue[3];
double B[3] = { -6.648457, 19.483239, 0.351848};

void initializeMpu() {
  if (!imu.Begin()) {
    Serial.println("IMU initialization unsuccessful");
    while (1) {}
  }
}
double getCurrentHeading() {
  if (imu.Read()) {
    double x[] = {imu.mag_x_ut(), imu.mag_y_ut(), imu.mag_z_ut()};
    minusB(x);
    produitMatricielle(x);
    return (atan2(calibratedValue[0], calibratedValue[1]) * 180.0 / M_PI);
  }
  return 0.0;
}
void minusB(double *x) {
  for (int i = 0; i < 3; i++) {
    *(x + i) -= B[i];
  }
}
void produitMatricielle(double *x) {
  for (int i = 0; i < 3; i++) {
    calibratedValue[i] = A[i][0] * (*(x)) + A[i][1] * (*(x + 1)) + A[i][2] * (*(x + 2));
  }
}
