#include "Servos.h"

Servos::Servos() {}

void Servos::init(int panPin, int tiltPin) {
    pan.attach(panPin, 500, 2500);
    tilt.attach(tiltPin, 500, 2500);
    resetPosition();
}

int Servos::readPan() {
    return pan.read();
}

int Servos::readTilt() {
    return tilt.read();
}

void Servos::setPosition(int azimuth, int elevation, int heading) {
    if(azimuth == 360) azimuth = 0;
    int16_t absAzimuth = azimuth - heading - 90;
    absAzimuth = absAzimuth < 0 ? 360 + absAzimuth : absAzimuth;
    if(absAzimuth > 180 && absAzimuth <= 360) {
        absAzimuth -= 180;
        elevation = 180 - elevation;
    }
    pan.write(azimuth);
    tilt.write(elevation);
}

void Servos::resetPosition() {
    pan.write(90);
    tilt.write(0);
}