#define ena 6
#define in1 7
#define in2 8
#define in3 9
#define in4 10
#define enb 11
double kp = 1, ki = 0, kd = 0;
int output = 0;
int currentH = 0, targetH = 0;
int error = 0, errorSum = 0, lastError = 0;
double latg = 0, longg = 0;
int active = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);

  initializeMpu();
  initializeRadio()
  Serial.begin(9600);
  while (!updateLocation()) Serial.println("waiting for gps data");
}

void loop() {
  // put your main code here, to run repeatedly:
  tuneValues(&kp, &ki, &kd, &active);
  if (active) {
    while (getDistance(latg, longg) < 3) {
      analogWrite(ena, 0);
      analogWrite(enb, 0);
    }
    updateLocation();
    currentH = getCurrentHeading();
    targetH = getTargetHeading(latg, longg);
    lastError = error;
    error = (currentH - targetH) % 180;
    errorSum += error;
    output = kp * error + ki * errorSum + kd * (error - lastError);
    if (output > 255)output = 255;
    else if (output < -255)output = -255;
    analogWrite(ena, 255 - output);
    analogWrite(enb, 255 + output);
  }
}
