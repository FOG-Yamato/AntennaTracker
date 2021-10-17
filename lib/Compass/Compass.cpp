#include "Compass.h"

Compass::Compass() {}

void Compass::init(int sda, int scl, uint32_t freq) {
    Wire.begin(sda, scl, freq);
    writeReg(0x0B, 0x01);
    configure(CONTINUOUS | RATE_200HZ | SCALE_8G | SAMPLE_512);
}

void Compass::read() {
    Wire.beginTransmission(MAG_ADDR);
    Wire.write(0x00);
    if(!Wire.endTransmission()) {
        Wire.requestFrom(MAG_ADDR, 0x06);
        int x = (int16_t)(Wire.read() | Wire.read() << 8);
        int y = (int16_t)(Wire.read() | Wire.read() << 8);
        int z = (int16_t)(Wire.read() | Wire.read() << 8);
        
        if(calibrated) {
            x = (x - calibration[OFFSET][X]) * calibration[DELTA][X];
            y = (y - calibration[OFFSET][Y]) * calibration[DELTA][Y];
            z = (z - calibration[OFFSET][Z]) * calibration[DELTA][Z];
        }
        switch(alligment) {
            default:
            case CW0:
                magData[X] = x;
                magData[Y] = y;
                magData[Z] = z;
                break;
            case CW90:
                magData[X] = y;
                magData[Y] = -x;
                magData[Z] = z;
                break;
            case CW180:
                magData[X] = -x;
                magData[Y] = -y;
                magData[Z] = z;
                break;
            case CW270:
                magData[X] = -y;
                magData[Y] = x;
                magData[Z] = z;
                break;
            case CW0_FLIP:
                magData[X] = -x;
                magData[Y] = y;
                magData[Z] = -z;
                break;
            case CW90_FLIP:
                magData[X] = y;
                magData[Y] = x;
                magData[Z] = -z;
                break;
            case CW180_FLIP:
                magData[X] = x;
                magData[Y] = -y;
                magData[Z] = -z;
                break;
            case CW270_FLIP:
                magData[X] = -y;
                magData[Y] = -x;
                magData[Z] = -z;
                break;
        }
    }
}

void Compass::setCalibration(int x_min, int x_max, int y_min, int y_max, int z_min, int z_max) {
    calibration[OFFSET][X] = (x_max + x_min)/2;
    calibration[OFFSET][Y] = (y_max + y_min)/2;
    calibration[OFFSET][Z] = (z_max + z_min)/2;
    int mainDelta = ((x_max - x_min)/2 + (y_max - y_min)/2 + (z_max - z_min)/2)/3;
    calibration[DELTA][X] = mainDelta/(x_max - x_min)/2;
    calibration[DELTA][Y] = mainDelta/(y_max - y_min)/2;
    calibration[DELTA][Z] = mainDelta/(z_max - z_min)/2;
    calibrated = true;
}

void Compass::setAlligment(compass_allign alg) {
    alligment = alg;
}

void Compass::setDeclination(double decl) {
    declination = decl;
}

int Compass::getAzimuth() {
    int arc = atan2(magData[Y], magData[X]) * 180/PI + declination;
    return arc < 0 ? 360 + arc : arc;
}

byte Compass::getBearing() {
    unsigned long segment = getAzimuth()/22.5;
    unsigned long remainder = segment - (int)segment;
    return (byte)((remainder >= 0.5) ? ceil(segment): floor(segment));
}

void Compass::reset() {
    writeReg(0x0A, 0x80);
}

void Compass::configure(byte conf) {
    writeReg(MAG_CONF_ADDR, conf);
}

void Compass::writeReg(byte addr, byte val) {
    Wire.beginTransmission(MAG_ADDR);
    Wire.write(addr);
    Wire.write(val);
    Wire.endTransmission();
}