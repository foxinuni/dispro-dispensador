#include <BluetoothSerial.h>
#include <ESP32Servo.h>
#include <Ds1302.h>

#include "command.h"
#include "drop.h"
#include "buzzer.h"
#include "display.h"

#define BT_NAME "Pawfedly"

#define PIN_CLK_RST 16
#define PIN_CLK_DAT 17
#define PIN_CLK_CLK 5
#define PIN_SERVO 2
#define PIN_BUZZER 4
#define PIN_ROM_DAT 18
#define PIN_ROM_CLK 19
#define PIN_SND_ECH 13
#define PIN_SND_TRG 12

static int SEGMENT_PINS[8] = {27, 32, 36, 34, 35, 22};
static int DIGIT_PINS[4] = {14, 25, 33, 23};

static Servo servo;
static CommandHandler handler;
static Ds1302 rtc(PIN_CLK_RST, PIN_CLK_CLK, PIN_CLK_DAT);
static BuzzerController buzzer_controller(melody, NOTES, PIN_BUZZER);
static DropController drop_controller(rtc, servo, buzzer_controller);
static SegmentDisplay segment_display(rtc, DIGIT_PINS, SEGMENT_PINS);

Ds1302::DateTime parse_time(const char* time_str) {
  Ds1302::DateTime now;

  char hour_str[3] = { time_str[0], time_str[1], '\0' };
  char minute_str[3] = { time_str[2], time_str[3], '\0' };
  char second_str[3] = { time_str[4], time_str[5], '\0' };
  
  // parse time
  now.hour = atoi(hour_str);
  now.minute = atoi(minute_str);
  now.second = atoi(second_str);

  return now;
}

void time_to_string(Ds1302::DateTime now, char* buffer) {
  sprintf(buffer, "%02d:%02d:%02d", now.hour, now.minute, now.second);
}

void echo(int argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
    Serial.print(argv[i]);
  }

  Serial.println("");
}

void get_time(int argc, char* argv[]) {
  // Se obtiene la hora
  Ds1302::DateTime now;
  rtc.getDateTime(&now);

  // Se convierte la hora a string
  char buffer[50];
  time_to_string(now, buffer);

  // Se publica la hora
  handler.publish(buffer);
  handler.publish("\n");
}

void set_time(int argc, char* argv[]) {
  if (argc < 1 || strlen(argv[1]) < 6) {
    handler.publish("expected time as a hhmmss");
    return;
  }

  // set time
  Ds1302::DateTime now = parse_time(argv[1]);
  rtc.setDateTime(&now);
}

void set_schedule(int argc, char* argv[]) {
  Ds1302::DateTime schedule[10];

  for (int i = 1; i < argc; i++) {
    schedule[i - 1] = parse_time(argv[i]);

    // Se imprime la hora
    char buffer[50];
    time_to_string(schedule[i - 1], buffer);

    Serial.print(i);
    Serial.print(" -> ");
    Serial.println(buffer);
  }
  
  // Save the schedule
  drop_controller.set_schedule(argc - 1, schedule);
}


void get_schedule(int argc, char* argv[]) {
  char buffer[50];
  Ds1302::DateTime schedule[10];
  
  // Obtain the schedule
  int count = drop_controller.get_schedule(schedule);

  // Send count
  sprintf(buffer, "%d ", count);
  handler.publish(buffer);

  // Send times
  for (int i = 0; i < count; i++) {
    time_to_string(schedule[i], buffer);
    handler.publish(buffer);
    handler.publish(" ");
  }

  handler.publish("\n");
}

void drop(int argc, char* argv[]) {
  drop_controller.drop();
}

void play(int argc, char* argv[]) {
  buzzer_controller.play();
}

void setup() {
  // Initialize serial
  Serial.begin(115200);

  // sInitialize the real time clock
  rtc.init();

  // Initialize the servo
  servo.attach(PIN_SERVO);

  // Initialize the drop controller
  drop_controller.init();

  // Initialize clock
  segment_display.init();

  // Initialize the command handler
  handler.subscribe("echo", echo);
  handler.subscribe("get-time", get_time);
  handler.subscribe("set-time", set_time);
  handler.subscribe("set-sch", set_schedule);
  handler.subscribe("get-sch", get_schedule);
  handler.subscribe("drop", drop);
  handler.subscribe("play", play);

  if (!handler.init(BT_NAME)) {
    Serial.println("Failed to initialized command handler!");
  }
}

void loop() { 
  // update the command handler
  handler.update();
  drop_controller.update();
  buzzer_controller.update();
  segment_display.update();
}
