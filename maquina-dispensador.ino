#include <BluetoothSerial.h>
#include <Ds1302.h>

#include "command.h"

#define BT_NAME "Pawfedly"

#define PIN_CLK_RST 5
#define PIN_CLK_DAT 18
#define PIN_CLK_CLK 19

static CommandHandler handler;
static Ds1302 rtc(PIN_CLK_RST, PIN_CLK_CLK, PIN_CLK_DAT);

void echo(int argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
    Serial.println(argv[i]);
  }
}

void get_time(int argc, char* argv[]) {
  // Se obtiene la hora
  Ds1302::DateTime now;
  rtc.getDateTime(&now);

  char buffer[50];
  sprintf(buffer, "%02d:%02d:%02d\n", now.hour, now.minute, now.second);
  Serial.print(buffer);

  handler.publish(buffer);
}

void setup() {
  Serial.begin(115200);

  // Initialize the real time clock
  rtc.init(); 

  // Initialize the command handler
  handler.subscribe("echo", echo);
  handler.subscribe("get-time", get_time);

  if (!handler.init(BT_NAME)) {
    Serial.println("Failed to initialized command handler!");
  }
}

void loop() { 
  // update the command handler
  handler.update();
}
