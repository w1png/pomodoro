CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags gtk4` `pkg-config --cflags json-c`
LDFLAGS = `pkg-config --libs gtk4` `pkg-config --libs json-c`
BUILD_DIR = build
SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
APP_NAME = pomodoro-gtk

all: $(APP_NAME)

$(APP_NAME): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(APP_NAME)

run: $(APP_NAME)
	./$(APP_NAME)
