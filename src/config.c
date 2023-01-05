#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <json-c/json.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

struct config {
  int pomodoro;
  int short_break;
  int long_break;
};

const struct config DEFAULT_CONFIG = {
  .pomodoro = 25,
  .short_break = 5,
  .long_break = 15
};

char *get_config_dir() {
  char *config_dir = malloc(200);
  sprintf(config_dir, "%s/.config/pomodoro/", getenv("HOME"));
  return config_dir;
}

void write_config(struct config config) {
  char *config_dir = get_config_dir();
  char *config_path = malloc(strlen(config_dir) + strlen("config.json"));
  sprintf(config_path, "%s%s", config_dir, "config.json");

  FILE *config_file = fopen(config_path, "w");
  if(config_file == NULL) {
    printf("Error opening config file");
    exit(1);
  }

  fprintf(config_file, "{\n");
  fprintf(config_file, "  \"pomodoro\": %d,\n", config.pomodoro);
  fprintf(config_file, "  \"short_break\": %d,\n", config.short_break);
  fprintf(config_file, "  \"long_break\": %d\n", config.long_break);
  fprintf(config_file, "}");
  fclose(config_file);

  free(config_dir);
  free(config_path);
}

struct stat st = {0};
void create_default_config() {
  char *config_dir = get_config_dir();
  char *config_path = malloc(strlen(config_dir) + strlen("config.json"));
  sprintf(config_path, "%s%s", config_dir, "config.json");
  
  if(stat(config_dir, &st) == -1) {
    mkdir(config_dir, 777);
  }
  free(config_dir);

  FILE *config_file = fopen(config_path, "w");
  if(config_file == NULL) {
    printf("Error creating config file");
    exit(1);
  }
  free(config_path);

  write_config(DEFAULT_CONFIG);
}

struct config read_config() {
  char *config_dir = get_config_dir();
  char *config_path = malloc(strlen(config_dir) + strlen("config.json"));
  sprintf(config_path, "%s%s", config_dir, "config.json");

  FILE *fp;
  fp = fopen(config_path, "r");
  if (fp == NULL) {
    printf("Error opening file\nTrying to create config file\n");
    create_default_config();
 } 

  struct json_object *parsed_json;
  struct json_object *pomodoro;
  struct json_object *short_break;
  struct json_object *long_break;

  parsed_json = json_object_from_file(config_path);

  json_object_object_get_ex(parsed_json, "pomodoro", &pomodoro);
  json_object_object_get_ex(parsed_json, "short_break", &short_break);
  json_object_object_get_ex(parsed_json, "long_break", &long_break);

  struct config config = {
    .pomodoro = json_object_get_int(pomodoro),
    .short_break = json_object_get_int(short_break),
    .long_break = json_object_get_int(long_break)
  };

  free(config_dir);
  free(config_path);

  return config;
}
