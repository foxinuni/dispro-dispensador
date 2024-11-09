#ifndef _MD_COMMAND_H
#define _MD_COMMAND_H

#include <BluetoothSerial.h>
#include <string>

#define BUFFER_SIZE 255
#define MAX_COMMANDS 10
#define MAX_ARGS 10

typedef void (*handler_fn)(int argc, char* argv[]);

struct Command {
  const char* name;
  handler_fn handler;
};

class CommandHandler {
private:
  int position;
  char buffer[BUFFER_SIZE];

  int count;
  Command commands[MAX_COMMANDS];

  BluetoothSerial client;

  int parse(char* data, char* values[]);
public:
  CommandHandler();
  bool init(const char* name);
  void publish(const char* msg);
  void subscribe(const char* name, handler_fn handler);
  void update();
};

#endif // _MD_COMMAND_H