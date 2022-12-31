#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int* parse_args(int argc, char *argv[]) {
  // args are 
  // -w work_time int
  // -b break_time int
  // -l long_break_time int
  // -h help

  int *args = malloc(3 * sizeof(int));
  args[0] = 25;
  args[1] = 5;
  args[2] = 15;
  
  char* help_str = "Usage: pomodoro [OPTION]\n Arguments:\n -w work_time int\n -b break_time int\n -l long_break_time int\n -h help\n";

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      switch (argv[i][1]) {
        case 'w':
          args[0] = atoi(argv[i+1]);
          break;
        case 'b':
          args[1] = atoi(argv[i+1]);
          break;
        case 'l':
          args[2] = atoi(argv[i+1]);
          break;
        case 'h':
          printf("%s", help_str);
          exit(0);
          break;
        default:
          printf("%s", help_str);
          exit(0);
          break;
      }
    }
  }
  return args;
}

void clear_console() {
  system("clear");
}

char* zero_pad(int n) {
  char* res = malloc(3 * sizeof(char));
  if (n < 10) {
    sprintf(res, "0%d", n);
  } else {
    sprintf(res, "%d", n);
  }
  return res;
}

void start_timer(char* prefix, int time_minutes) {
  int time_seconds = time_minutes * 60;

  for (int i = 0; i < time_seconds; i++) {
    int minutes = (time_seconds - i) / 60;
    int seconds = (time_seconds - i) % 60;

    clear_console();
    
    char* echo_cmd = malloc(100 * sizeof(char));
    sprintf(echo_cmd, "echo \"%s\"", prefix);
    system(echo_cmd);
    // printf("%s", prefix);
    char* figlet_command = malloc(30 * sizeof(char));
    sprintf(figlet_command, "figlet -f $HOME/dev/c/pomodoro/font.flf %s:%s", zero_pad(minutes), zero_pad(seconds));
    system(figlet_command);

    sleep(1);
  }
}

int main(int argc, char *argv[]) {
  int *args = parse_args(argc, argv);

  char* WORK_PREFIX = "Work time left: ";
  char* BREAK_PREFIX = "Break time left: ";

  while (1) {
    for (int i = 0; i < 3; i++) {
      start_timer(WORK_PREFIX, args[0]);
      start_timer(BREAK_PREFIX, args[1]);
    }
    start_timer(WORK_PREFIX, args[0]);
    start_timer(BREAK_PREFIX, args[2]);
  }
}
