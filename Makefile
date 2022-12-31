# compile main.c
# make run to compile and run

CC = gcc

main: main.c
	$(CC) -o pomodoro-cli main.c

run: main
	./main

install: main
	cp pomodoro-cli /usr/local/bin/pomodoro-cli

uninstall:
	rm /usr/local/bin/pomodoro-cli

