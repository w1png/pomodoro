#include <stdio.h>
#include "config.h"
#include "ui.h"

int main (int argc, char **argv) {
  struct config config = read_config();
  int status = -1;
  status = init_ui(
    config.pomodoro,
    config.short_break,
    config.long_break
  );

  return status;
}

