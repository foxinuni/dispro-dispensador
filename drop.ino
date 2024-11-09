#include "drop.h"

DropController::DropController(Ds1302& rtc) : rtc(rtc) {
  // Get the current time
  Ds1302::DateTime time;
  this->rtc.getDateTime(&now);

  // Load schedule from EEPROM
  this->count = 0;
  for (int i = 0; i < this->count; i++) {
    
  }
}