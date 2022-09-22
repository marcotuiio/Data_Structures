EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
PROJECT_NAME = ted

clear: 
	rm *.o
	rm *.dot
	rm $(PROJECT_NAME)

$(PROJECT_NAME): main.o teste.o
	$(EXEC) $(CFLAGS) main.o teste.o -o $(PROJECT_NAME)

teste.o: teste.c red_black_tree.h
	$(EXEC) $(CFLAGS) -c teste.c

main.o: main.c 
	$(EXEC) $(CFLAGS) -c main.c
