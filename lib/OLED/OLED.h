#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

class OLED {
    public:
        void init();
        void displayData(int sats, int azm, double lat, double lng, double alt, double tlmLat, double tlmLng);
    private:
        int line;
        int row;
        void resetCursor();
        void drawText(String str);
        void drawText(int num);
        void drawText(double num, int prec = 0);
        void drawTextln(String str);
        void drawTextln(int num);
        void drawTextln(double num, int prec = 0);
        int calculateLength(String str);
        int calculateLength(int num);
        int calculateLength(double num, int prec = 0);
};