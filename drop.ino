#include "drop.h"
#include <EEPROM.h>

bool time_greater(Ds1302::DateTime time, Ds1302::DateTime next) {
  return next.hour > time.hour 
    || (next.hour == time.hour && next.minute > time.minute) 
    || (next.hour == time.hour && next.minute == time.minute && next.second > time.second);
}

DropController::DropController(Ds1302& rtc, Servo& servo, BuzzerController& buzzer_controller) : rtc(rtc), servo(servo), buzzer_controller(buzzer_controller) {
  this->count = 0;
  this->dropped = false;
  this->dropped_since = 0;
  this->timeout_since = 0;
  this->state = DropControllerState::IDLE;
}

void DropController::init() {
  // Load schedule from EEPROM
  this->load();

  // Calculate next drop
  this->calculate_next();
}

void DropController::calculate_next() {
  // Get the current time
  Ds1302::DateTime time;
  this->rtc.getDateTime(&time);

  for (int i = 0; i < this->count; i++) {
    Ds1302::DateTime next = this->schedule[i];
    
    if (time_greater(time, next)) {
      this->next = i;
      break;
    }
  }
}

void DropController::load() {
  SavedSchedule saved;

  Serial.println("Loading saved schedule from EEPROM");

  // Load from EEPROM
  int address = 0;  // Starting address in EEPROM
  uint8_t *dataPtr = (uint8_t*) &saved;  // Pointer to the struct as bytes
  
  for (size_t i = 0; i < sizeof(SavedSchedule); i++) {
    *dataPtr++ = EEPROM.read(address++);  // Read each byte from EEPROM
    Serial.print(*(dataPtr - 1));
  }
  Serial.println("");

  // Load the data to the class
  if (saved.initialized == 0xFF) {
    this->count = saved.count;
    
    for (int i = 0; i < saved.count; i++) {
      this->schedule[i] = saved.schedule[i];
    }
  }
}

void DropController::save() {
  SavedSchedule saved = {
    .initialized = 0xFF,
    .count = this->count
  };

  for (int i = 0; i < this->count; i++) {
    saved.schedule[i] = this->schedule[i];
  }

  Serial.println("Writing saved schedule to EEPROM");

  int address = 0;  // Starting address in EEPROM
  uint8_t *dataPtr = (uint8_t*) &saved;  // Pointer to the struct as bytes

  for (size_t i = 0; i < sizeof(SavedSchedule); i++) {
      Serial.print(*dataPtr);
      EEPROM.put(address++, *dataPtr++);  // Write each byte to EEPROM
  }

  Serial.println("");
}

void DropController::drop() {
  this->dropped = true;
  this->dropped_since = millis();
  this->servo.write(SERVO_MAX);
}

void DropController::update() {
  if (dropped && millis() - dropped_since >= DROP_TIME) {
    this->servo.write(SERVO_MIN);
    this->dropped = false;
  }

  switch (this->state) {
    case DropControllerState::IDLE: {
      // Get the current time
      Ds1302::DateTime now;
      this->rtc.getDateTime(&now);

      // Get the next drop time
      Ds1302::DateTime drop_time = this->schedule[this->next];

      if (this->count > 0 && time_greater(now, this->schedule[0])) {
        this->next = 0;
      }
      
      if (this->count > this->next && !time_greater(now, drop_time)) {
        this->next = this->next + 1;
        this->timeout_since = millis();
        this->fails = 0;
        this->drop();
        this->buzzer_controller.play();
        
        // read pet
        this->state = DropControllerState::DROPPED;
      }

      break;
    }
    case DropControllerState::DROPPED: {
      // read pet

      if (millis() - this->timeout_since >= TIMEOUT) {
        this->state = DropControllerState::PET_CHECK;
      }

      break;
    }
    case DropControllerState::PET_CHECK: {
      // check if pet has arrived
      if (true) {
        this->state = DropControllerState::IDLE;
      } else {
        this->fails++;
        this->state = DropControllerState::RETRY;
      }

      break;
    }
    case DropControllerState::RETRY: {
      if (this->fails >= 3) {
        this->state = DropControllerState::IDLE;
      } else {
        this->buzzer_controller.play();
        this->timeout_since = millis();
        this->state = DropControllerState::DROPPED;
      }

      break;
    }
  }
}

void DropController::set_schedule(int count, Ds1302::DateTime schedule[]) {
  if (count > SCHEDULE_MAX) {
    count = SCHEDULE_MAX;
  }

  // Set count
  this->count = count;

  // Set schedule
  for (int i = 0; i < count; i++) {
    this->schedule[i] = schedule[i];
  }

  // Calculate next
  this->calculate_next();

  // Save the data
  this->save();
}

int DropController::get_schedule(Ds1302::DateTime schedule[]) {
  for (int i = 0; i < this->count; i++) {
    schedule[i] = this->schedule[i];
  }

  return this->count;
}