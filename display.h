#ifndef DISPLAY_H
#define DISPLAY_H

#include <Ds1302.h>

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
    int* digits_pins;
    int* segment_pins;
    Ds1302& rtc;

public:
    SegmentDisplay(Ds1302& rtc, int digits_pins[4], int segment_pins[8]);

    void init();
    void update();
    void set_digit(int index, int value);
};

#endif