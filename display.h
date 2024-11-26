#ifndef DISPLAY_H
#define DISPLAY_H

#include <Ds1302.h>
#include <SevSeg.h>

#define SEG_A 0
#define SEG_B 1
#define SEG_C 2
#define SEG_D 3
#define SEG_E 4
#define SEG_F 5
#define SEG_G 6
#define SEG_DP 7

class SegmentDisplay {
private:
    Ds1302& rtc;
    SevSeg& sevseg;

public:
    SegmentDisplay(Ds1302& rtc, SevSeg& sevseg);
    void init(unsigned char digits[4], unsigned char segments[8]);
    void update();
};

#endif