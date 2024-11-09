#include "command.h"
#include <string.h>

CommandHandler::CommandHandler() {
  this->position = 0;
  this->count = 0;
}

bool CommandHandler::init(const char* name) {
  return this->client.begin(name);
}

int CommandHandler::parse(char* data, char* values[]) {
  int count = 0;

  char* token = strtok(data, " ");
  do {
    values[count] = token;
    count++;
  } while (token = strtok(NULL, " "));

  return count;
}

void CommandHandler::publish(const char* msg) {
  int len = strlen(msg);

  for (int i = 0; i < len; i++) {
    this->client.write(msg[i]);
  }
}

void CommandHandler::subscribe(const char* name, handler_fn handler) {
  if (this->count >= MAX_COMMANDS) {
    return;
  }

  Serial.print("registering command: ");
  Serial.println(name);

  Command command = { name, handler };
  this->commands[this->count] = command;
  this->count++;
}

void CommandHandler::update() {
  if (this->client.available()) {
    char byte = this->client.read();

    if (byte == '\n') {
      this->buffer[this->position] = '\0';
      this->position = 0;

      Serial.print("incomming command: ");
      Serial.println(this->buffer);

      char* argv[MAX_ARGS];
      int argc = this->parse(this->buffer, argv);

      for (int i = 0; i < this->count; i++) {
        Command command = this->commands[i];

        if (argc > 0 && !strcmp(command.name, argv[0])) {
          command.handler(argc, argv);
        }
      }
    } else {
      this->buffer[this->position] = byte;
      this->position++;
    }
  }
}

