#include "common.h"

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, GPS_RX, GPS_TX);
  BT.begin("Tracker", true);
  BT.connect("tx16s");
  mag.init();
  mag.setDeclination(6.56);
  servos.init(SERVO_PAN, SERVO_TILT);
  display.init();
  pinMode(BUTTON, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.println("Tracker Start");
}


void loop() {
  mag.read();
  // @TODO: Add GPS autodetection and autoconfiguration
  GPS.encode(char(Serial1.read()));
  if(BT.available()) {
    crsf.read(char(BT.read()));
  } 
  // @TODO: Add homepoint setup after GPS lock
  // @TODO: Add position calculation and servo set via servos.setPosition()
  display.displayData(GPS.satellites.value(), mag.getAzimuth(), GPS.location.lat(), GPS.location.lng(), GPS.altitude.meters(), crsf.getLat(), crsf.getLng());
}