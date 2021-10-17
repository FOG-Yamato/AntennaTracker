#include <Wire.h>
#include <Arduino.h>

typedef enum {
    NONE = 0,
    CW0 = 1,
    CW90 = 2,
    CW180 = 3,
    CW270 = 4,
    CW0_FLIP = 5,
    CW90_FLIP = 6,
    CW180_FLIP = 7,
    CW270_FLIP = 8
} compass_allign;

typedef enum {
    X = 0,
    Y = 1,
    Z = 2
};

typedef enum {
    OFFSET = 0,
    DELTA = 1
};

#define MAG_ADDR 0x0D
#define MAG_CONF_ADDR 0x09
typedef enum {
    STANDBY = 0x0,
    CONTINUOUS = 0x01
} modes;
typedef enum {
    RATE_10HZ = 0x00,
    RATE_50HZ = 0x04,
    RATE_100HZ = 0x08,
    RATE_200HZ = 0x0C
} rates;
typedef enum {
    SCALE_2G = 0x00,
    SCALE_8G = 0x10
} scale;
typedef enum {
    SAMPLE_64 = 0xC0,
    SAMPLE_128 = 0x80,
    SAMPLE_256 = 0x40,
    SAMPLE_512 = 0x00
} sample_ratio;

class Compass {
    public:
        Compass();
        void init(int sda = -1, int scl = -1, uint32_t freq = 0U);
        void read();
        void setCalibration(int x_min, int x_max, int y_min, int y_max, int z_min, int z_max);
        void setAlligment(compass_allign alg);
        void setDeclination(double decl);
        int getAzimuth();
        byte getBearing();
        void reset();
        void configure(byte conf);
        bool calibrate();
    private:
        void writeReg(byte addr, byte val);
        byte magAddr = MAG_ADDR;
        int magData[3] = {0,0,0};
        float calibration[2][3];
        bool calibrated = false;
        double declination = 0.0;
        compass_allign alligment = CW270_FLIP;
};