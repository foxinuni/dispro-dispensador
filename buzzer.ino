#include "buzzer.h"

#include <driver/ledc.h>
#include <esp_err.h>


void BuzzerController::play() {
    //should_play = true;
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
                //ledcWriteNote(pin, melody[note].frecuency, 8);

                time = prev = millis();
                state = BuzzerControllerState::AWAIT_NOTE;
            } else {
                state = BuzzerControllerState::IDLE;
            }

            break;
        case BuzzerControllerState::AWAIT_NOTE:
            if (millis() - time >= melody[note].length) {
                //ledcWriteNote(pin, 0, 8);
                note++;
                state = BuzzerControllerState::NEXT_NOTE;
            }

            break;
    }
}