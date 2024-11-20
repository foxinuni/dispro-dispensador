#ifndef BUZZER_H
#define BUZZER_H

#define NOTES 14

class Note {
public:
    long length;
    long frecuency;
};

Note melody[NOTES] = {
    {500, 523},  // DO, 1000ms
    {500, 523},  // DO, 1000ms
    {500, 784},  // SOL, 1000ms
    {500, 784},  // SOL, 1000ms
    {500, 880},  // LA, 1000ms
    {500, 880},  // LA, 1000ms
    {1000, 784},  // SOL, 1500ms
    {500, 698},  // FA, 1000ms
    {500, 698},  // FA, 1000ms
    {500, 659},  // MI, 1000ms
    {500, 659},  // MI, 1000ms
    {500, 587},  // RE, 1000ms
    {500, 587},  // RE, 1000ms
    {500, 523},  // DO, 1000ms
};

enum class BuzzerControllerState {
    IDLE,
    NEXT_NOTE,
    AWAIT_NOTE,
};

class BuzzerController {
private:
    Note* melody;
    BuzzerControllerState state;
    int notes;
    int pin;
    int fallas;
    int note;
    int time, prev;
    long dc;
    long cicles, cicle;
    bool should_play;
public:
    BuzzerController(Note* melody, int notes, int pin): melody(melody), notes(notes), pin(pin) {
        //ledcAttach(pin, 0, 8);
        state = BuzzerControllerState::IDLE;
        should_play = false;
    }

    void play();
    void update();
};

#endif