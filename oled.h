#ifndef _MD_OLED_H
#define _MD_OLED_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define WIDTH 128
#define HEIGHT 32

class OledDisplay {
private:
  Adafruit_SSD1306 display;
public:
  OledDisplay();
};

#endif // _MD_OLED_H