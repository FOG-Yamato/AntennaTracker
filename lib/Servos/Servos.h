#include <ESP32Servo.h>

class Servos {
    public:
        Servos();
        void init(int pan, int tilt);
        int readPan();
        int readTilt();
        void setPosition(int azimuth, int elevation, int heading);
        void resetPosition();
    private:
        Servo pan;
        Servo tilt;
};