#include <Arduino.h>
#include <SPI.h>
#include <TinyGPS++.h>
#include <Compass.h>
#include <Servos.h>
#include <OLED.h>
#include <BluetoothSerial.h>
#include <CRSF.h>

#define GPS_RX 16
#define GPS_TX 17
#define I2C_SDA 21
#define I2C_SCL 22

#define SERVO_PAN 13
#define SERVO_TILT 12

#define BUTTON 26
#define BUZZER 14
#define LED 27

#define FONT u8g2_font_5x7_tr
#define FONT_WIDTH 5
#define FONT_HEIGHT 7

#define OLED_CS 5
#define OLED_DC 4
#define OLED_RST 2

TinyGPSPlus GPS;
Compass mag;
Servos servos;
OLED display;
BluetoothSerial BT;
CRSF crsf;