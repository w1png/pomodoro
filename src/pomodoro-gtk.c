#include<stdio.h>
#include "config.h"

void read_and_print_config() {
  struct config config = read_config();
  printf("Pomodoro: %d\n", config.pomodoro);
  printf("Short Break: %d\n", config.short_break);
  printf("Long Break: %d\n", config.long_break);
}

int main (int argc, char **argv) {

  read_and_print_config();
  struct config new_config = {
    .pomodoro = 50,
    .short_break = 10,
    .long_break = 20
  };
  write_config(new_config);
  read_and_print_config();

  return 0;
}

