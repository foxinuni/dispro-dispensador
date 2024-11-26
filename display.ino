#include "display.h"

#include <SevSeg.h>

SegmentDisplay::SegmentDisplay(Ds1302& rtc, SevSeg& sevseg) : rtc(rtc), sevseg(sevseg) {}

void SegmentDisplay::init(unsigned char digits[4], unsigned char segments[8]) {
  this->sevseg.begin(COMMON_CATHODE, 4, digits, segments, false);
  this->sevseg.setBrightness(50);
}

void SegmentDisplay::update() {
  Ds1302::DateTime time;
  this->rtc.getDateTime(&time);

  int d1 = time.hour / 10;
  int d2 = time.hour % 10;
  int d3 = time.minute / 10;
  int d4 = time.minute % 10;

  int number = d1 * 1000 + d2 * 100 + d3 * 10 + d4;

  this->sevseg.setNumber(number, 2);
  this->sevseg.refreshDisplay();
}