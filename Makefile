CC = gcc
FLAGS = -Wall -Wextra -g
TARGETS = main.c functions.c satelite.c heap.c BST.c queue.c
NAME = tema2

build: $(TARGETS)
	$(CC) $(FLAGS) -o $(NAME) $(TARGETS)

run: build
	./$(NAME)

pack:
	zip -FSr NEACSALeonard-315CA.zip README Makefile *.c *.h

PHONY: clean
clean:
	rm -f $(NAME)