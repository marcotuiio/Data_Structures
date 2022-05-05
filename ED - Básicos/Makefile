EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
PROJECT_NAME = ted

clear: 
	rm *.o
	rm $(PROJECT_NAME)

$(PROJECT_NAME): main.o tree.o 
	$(EXEC) $(CFLAGS) main.o tree.o -o $(PROJECT_NAME)

tree.o: tree.c tree.h
	$(EXEC) $(CFLAGS) -c tree.c

main.o: main.c 
	$(EXEC) $(CFLAGS) -c main.c
