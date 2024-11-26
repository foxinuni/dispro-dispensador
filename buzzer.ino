#include "buzzer.h"

#include <driver/ledc.h>
#include <esp_err.h>

void BuzzerController::init() {
    if (!ledcAttachChannel(pin, 500, 7, LEDC_CHANNEL_5)) {
      Serial.println("Failed to attach buzzer pin");
    } 
}

void BuzzerController::play() {
    should_play = true;
}

void BuzzerController::update() {
      switch (state) {
        case BuzzerControllerState::IDLE:
            if (should_play) {
                should_play = false;
                note = 0;
                state = BuzzerControllerState::NEXT_NOTE;
            }

            break;
        case BuzzerControllerState::NEXT_NOTE:
            if (note < notes) {
                ledcWriteTone(pin, melody[note].frecuency);

                //tone(pin, melody[note].frecuency);

                time = prev = millis();
                state = BuzzerControllerState::AWAIT_NOTE;
            } else {
                state = BuzzerControllerState::IDLE;
            }

            break;
        case BuzzerControllerState::AWAIT_NOTE:
            if (millis() - time >= melody[note].length) {
                ledcWriteTone(pin, 0);

                //noTone(pin);
                note++;
                state = BuzzerControllerState::NEXT_NOTE;
            }

            break;
    }
}