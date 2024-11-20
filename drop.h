#ifndef _MD_DROP_H
#define _MD_DROP_H

#include "buzzer.h"
#include <Ds1302.h>
#include <ESP32Servo.h>

#define SCHEDULE_MAX 5
#define SERVO_MAX 90
#define SERVO_MIN 0
#define DROP_TIME 2000
#define TIMEOUT 30000

struct SavedSchedule {
  int initialized;
  int count;
  Ds1302::DateTime schedule[SCHEDULE_MAX];
};

enum class DropControllerState {
  IDLE,
  DROPPED,
  PET_CHECK,
  RETRY
};

class DropController {
private:
  int next;
  int count;
  int fails;
  bool dropped;
  int dropped_since;
  int timeout_since;
  Ds1302::DateTime schedule[SCHEDULE_MAX];
  DropControllerState state;
  Ds1302& rtc;
  Servo& servo;
  BuzzerController& buzzer_controller;

  void calculate_next();
  void load();
  void save();
public:
  DropController(Ds1302& rtc, Servo& servo, BuzzerController& buzzer_controller);
  void init();
  void drop();
  void update();
  void set_schedule(int count, Ds1302::DateTime schedule[]);
  int get_schedule(Ds1302::DateTime schedule[]);
};

#endif // _MD_DROP_H