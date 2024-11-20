#include "display.h"

SegmentDisplay::SegmentDisplay(Ds1302& rtc, int digits_pins[4], int segment_pins[8]) : rtc(rtc) {
    this->digits_pins = digits_pins;
    this->segment_pins = segment_pins;
}

void SegmentDisplay::init() {
    for (int i = 0; i < 4; i++) {
        pinMode(digits_pins[i], OUTPUT);
        digitalWrite(digits_pins[i], HIGH);
    }

    for (int i = 0; i < 8; i++) {
        pinMode(segment_pins[i], OUTPUT);
        digitalWrite(segment_pins[i], LOW);
    }
}

void SegmentDisplay::set_digit(int index, int value) {
    for (int i = 0; i < 4; i++) {
        digitalWrite(digits_pins[i], i == index ? LOW : HIGH);
    }

    switch (value) {
        case 0:
            digitalWrite(segment_pins[SEG_A], HIGH);
            digitalWrite(segment_pins[SEG_B], HIGH);
            digitalWrite(segment_pins[SEG_C], HIGH);
            digitalWrite(segment_pins[SEG_D], HIGH);
            digitalWrite(segment_pins[SEG_E], HIGH);
            digitalWrite(segment_pins[SEG_F], HIGH);
            digitalWrite(segment_pins[SEG_G], LOW);
            break;
        case 1:
            digitalWrite(segment_pins[SEG_A], LOW);
            digitalWrite(segment_pins[SEG_B], HIGH);
            digitalWrite(segment_pins[SEG_C], HIGH);
            digitalWrite(segment_pins[SEG_D], LOW);
            digitalWrite(segment_pins[SEG_E], LOW);
            digitalWrite(segment_pins[SEG_F], LOW);
            digitalWrite(segment_pins[SEG_G], LOW);
            break;
        case 2:
            digitalWrite(segment_pins[SEG_A], HIGH);
            digitalWrite(segment_pins[SEG_B], HIGH);
            digitalWrite(segment_pins[SEG_C], LOW);
            digitalWrite(segment_pins[SEG_D], HIGH);
            digitalWrite(segment_pins[SEG_E], HIGH);
            digitalWrite(segment_pins[SEG_F], LOW);
            digitalWrite(segment_pins[SEG_G], HIGH);
            break;
        case 3:
            digitalWrite(segment_pins[SEG_A], HIGH);
            digitalWrite(segment_pins[SEG_B], HIGH);
            digitalWrite(segment_pins[SEG_C], HIGH);
            digitalWrite(segment_pins[SEG_D], HIGH);
            digitalWrite(segment_pins[SEG_E], LOW);
            digitalWrite(segment_pins[SEG_F], LOW);
            digitalWrite(segment_pins[SEG_G], HIGH);
            break;
        case 4:
            digitalWrite(segment_pins[SEG_A], LOW);
            digitalWrite(segment_pins[SEG_B], HIGH);
            digitalWrite(segment_pins[SEG_C], HIGH);
            digitalWrite(segment_pins[SEG_D], LOW);
            digitalWrite(segment_pins[SEG_E], LOW);
            digitalWrite(segment_pins[SEG_F], HIGH);
            digitalWrite(segment_pins[SEG_G], HIGH);
            break;
        case 5:
            digitalWrite(segment_pins[SEG_A], HIGH);
            digitalWrite(segment_pins[SEG_B], LOW);
            digitalWrite(segment_pins[SEG_C], HIGH);
            digitalWrite(segment_pins[SEG_D], HIGH);
            digitalWrite(segment_pins[SEG_E], LOW);
            digitalWrite(segment_pins[SEG_F], HIGH);
            digitalWrite(segment_pins[SEG_G], HIGH);
            break;
        case 6:
            digitalWrite(segment_pins[SEG_A], HIGH);
            digitalWrite(segment_pins[SEG_B], LOW);
            digitalWrite(segment_pins[SEG_C], HIGH);
            digitalWrite(segment_pins[SEG_D], HIGH);
            digitalWrite(segment_pins[SEG_E], HIGH);
            digitalWrite(segment_pins[SEG_F], HIGH);
            digitalWrite(segment_pins[SEG_G], HIGH);
            break;
        case 7:
            digitalWrite(segment_pins[SEG_A], HIGH);
            digitalWrite(segment_pins[SEG_B], HIGH);
            digitalWrite(segment_pins[SEG_C], HIGH);
            digitalWrite(segment_pins[SEG_D], LOW);
            digitalWrite(segment_pins[SEG_E], LOW);
            digitalWrite(segment_pins[SEG_F], LOW);
            digitalWrite(segment_pins[SEG_G], LOW);
            break;
        case 8:
            digitalWrite(segment_pins[SEG_A], HIGH);
            digitalWrite(segment_pins[SEG_B], HIGH);
            digitalWrite(segment_pins[SEG_C], HIGH);
            digitalWrite(segment_pins[SEG_D], HIGH);
            digitalWrite(segment_pins[SEG_E], HIGH);
            digitalWrite(segment_pins[SEG_F], HIGH);
            digitalWrite(segment_pins[SEG_G], HIGH);
            break;
        case 9:
            digitalWrite(segment_pins[SEG_A], HIGH);
            digitalWrite(segment_pins[SEG_B], HIGH);
            digitalWrite(segment_pins[SEG_C], HIGH);
            digitalWrite(segment_pins[SEG_D], HIGH);
            digitalWrite(segment_pins[SEG_E], LOW);
            digitalWrite(segment_pins[SEG_F], HIGH);
            digitalWrite(segment_pins[SEG_G], HIGH);
            break;
        default:
            digitalWrite(segment_pins[SEG_A], LOW);
            digitalWrite(segment_pins[SEG_B], LOW);
            digitalWrite(segment_pins[SEG_C], LOW);
            digitalWrite(segment_pins[SEG_D], LOW);
            digitalWrite(segment_pins[SEG_E], LOW);
            digitalWrite(segment_pins[SEG_F], LOW);
            digitalWrite(segment_pins[SEG_G], LOW);
            break;
    }
}


void SegmentDisplay::update() {
    /*
    Ds1302::DateTime time;
    this->rtc.getDateTime(&time);

    set_digit(0, time.hour / 10);
    set_digit(1, time.hour % 10);
    set_digit(2, time.minute / 10);
    set_digit(3, time.minute % 10);
    */

    /*
    static int time = 0;
    static int i = 0;

    while (true) {
        if (millis() - time > 1000) {
            time = millis();
            i = (i + 1) % 10;
        } else {
            set_digit(0, i);
        }
    }
    */

    for (int i = 0; i < 8; i++) {
        digitalWrite(segment_pins[i], HIGH);
    }

    digitalWrite(digits_pins[0], LOW);
    digitalWrite(digits_pins[1], HIGH);
    digitalWrite(digits_pins[2], HIGH);
    digitalWrite(digits_pins[3], HIGH);
}