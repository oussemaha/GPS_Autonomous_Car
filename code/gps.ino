#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
TinyGPSPlus gps;
SoftwareSerial ss(4, 3);
double latc, longc;
bool updateLocation() {
  while (ss.available() > 0)
    if (gps.encode(ss.read())) {
      latc = gps.location.lat();
      longc = gps.location.lng();
      return true;
    }
    else return false;
}
double getTargetHeading(double latg, double longg) {
  double target = atan2(sin(longg - longc) * cos(longg), cos(longc) * sin(latg) - sin(latc) * cos(latg) * cos(longg - longc));
  return target;
}
double getDistance(double latg, double longg) {
  latg = latg * M_PI / 180.0;
  longg = longg * M_PI / 180.0;
  double longcR = longc * M_PI / 180.0, latcR = latc * M_PI / 180.0;
  double dlat = latg - latcR;
  double dlon = longg - longcR;
  double a = sin(dlat / 2) * sin(dlat / 2) + cos(latcR) * cos(latg) * sin(dlon / 2) * sin(dlon / 2);
  return 6371.0 * 2 * atan2(sqrt(a), sqrt(1 - a))*1000.0;
}
