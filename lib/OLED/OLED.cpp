#include "OLED.h"
#include "common.h"

U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI oled(U8G2_R0, OLED_CS, OLED_DC, OLED_RST);

void OLED::init() {
    oled.begin();
    oled.setFont(FONT);
    oled.clearBuffer();
}

void OLED::displayData(int sats, int azm, double lat, double lng, double alt, double tlmLat, double tlmLng) {
    oled.clearBuffer();
    resetCursor();
    drawText("Antenna Tracker Sats: ");
    drawTextln(sats);
    drawText("Azimuth:");
    drawTextln(azm);
    drawText("Lat:");
    drawTextln(lat, 6);
    drawText("Lng:");
    drawTextln(lng, 6);
    drawText("Alt:");
    drawTextln(String(alt, 1) + "m");
    drawText("TLM Lat:");
    drawTextln(tlmLat, 6);
    drawText("TLM Lng:");
    drawTextln(tlmLng, 6);
    oled.sendBuffer();
}

void OLED::resetCursor() {
    line = FONT_HEIGHT;
    row = 0;
}

void OLED::drawText(String str) {
    oled.drawStr(row, line, str.c_str());
    row += calculateLength(str);
}

void OLED::drawText(int num) {
    oled.drawStr(row, line, String(num).c_str());
    row += calculateLength(num);
}

void OLED::drawText(double num, int prec) {
    oled.drawStr(row, line, String(num, prec).c_str());
    row += calculateLength(num, prec);
}

void OLED::drawTextln(String str) {
    oled.drawStr(row, line, str.c_str());
    row = 0;
    line += FONT_HEIGHT+1;
}

void OLED::drawTextln(int num) {
    oled.drawStr(row, line, String(num).c_str());
    row = 0;
    line += FONT_HEIGHT+1;
}

void OLED::drawTextln(double num, int prec) {
    oled.drawStr(row, line, String(num, prec).c_str());
    row = 0;
    line += FONT_HEIGHT+1;
}

int OLED::calculateLength(String str) {
    return str.length()*FONT_WIDTH;
}

int OLED::calculateLength(int num) {
    return String(num).length()*FONT_WIDTH;
}

int OLED::calculateLength(double num, int prec) {
    return String(num, prec).length()*FONT_WIDTH;
}

