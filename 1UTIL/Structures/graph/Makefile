EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
PROJECT_NAME = ted

clear: 
	rm *.o
	rm *.dot
	rm $(PROJECT_NAME)

$(PROJECT_NAME): main.o list_graph.o list.o
	$(EXEC) $(CFLAGS) main.o list_graph.o list.o -o $(PROJECT_NAME)

list_graph.o: list_graph.c list_graph.h
	$(EXEC) $(CFLAGS) -c list_graph.c

list.o: list.c list.h
	$(EXEC) $(CFLAGS) -c list.c

main.o: main.c 
	$(EXEC) $(CFLAGS) -c main.c
