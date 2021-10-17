#include <Arduino.h>

#define CRSF_MAX_FRAME_SIZE 64


class CRSF {
    public:
        void read(char payload);
        float getLat();
        float getLng();
        float getSpeed();
        float getHdg();
        float getSats();
        float getAlt();

    private:
        uint8_t buffer[CRSF_MAX_FRAME_SIZE];
        uint8_t crcpoly = 0xD5;
        int ind = 0;
        bool process = false;
        float lat;
        float lng;
        float speed;
        float heading;
        int16_t alt;
        uint8_t sats;
        uint8_t calcCRC(uint8_t* data, int len);
        void resetState();
        void processPacket();
};