EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
PROJECT_NAME = teste

clear: 
	rm *.o
	rm $(PROJECT_NAME)

$(PROJECT_NAME): main.o red_black_tree.o
	$(EXEC) $(CFLAGS) main.o red_black_tree.o -o $(PROJECT_NAME)

red_black_tree.o: red_black_tree.c red_black_tree.h
	$(EXEC) $(CFLAGS) -c red_black_tree.c

main.o: main.c 
	$(EXEC) $(CFLAGS) -c main.c
