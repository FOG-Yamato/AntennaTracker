#include "CRSF.h"

uint8_t CRSF::calcCRC(uint8_t* data, int len) {
  uint8_t crc = 0;
  while(len--) {
    crc ^= *data++;
    for(int i = 0; i < 8; ++i) crc = crc & 0x80 ? ((crc << 1) ^ crcpoly) : (crc << 1);
  }
  return crc;
}

void CRSF::resetState() {
  process = false;
  ind = 0;
}

void CRSF::processPacket() {
  if(buffer[2] == 0x02) {
    lat = ((buffer[3] << 24) | (buffer[4] << 16) | (buffer[5] << 8) | buffer[6])/10000000L;
    lng = ((buffer[7] << 24) | (buffer[8] << 16) | (buffer[9] << 8) | buffer[10])/10000000L;
    speed = ((buffer[11] << 8) | buffer[12])/10;
    heading = ((buffer[13] << 8) | buffer[14])/1000;
    alt = ((buffer[15] << 8) | buffer[16])-1000;
    sats = buffer[17];
  }
}

void CRSF::read(char payload) {
  if(!process) {
    if(payload == 0xEA || payload == 0xC8) {
      process = true;
      ind = 0;
      buffer[ind] = payload;
      ind++;
    }
  } else {
    if(ind >= 64) resetState();
    if(ind == 1 && payload >= 64) resetState();
    buffer[ind] = payload;
    ind++;
    if(buffer[1] + 2 == ind) {
      char res = calcCRC(buffer + 2, buffer[1] - 1);
      if(res == payload) processPacket();
      else {
        Serial.println("CRC check failed, skipping packet...");
      }
      resetState();
    }
  }
}