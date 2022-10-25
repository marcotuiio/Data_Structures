EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
PROJECT_NAME = ted
OBJECTS = main.o list_graph.o list.o queue.o

clear: 
	rm *.o
	rm *.dot
	rm $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(EXEC) $(CFLAGS) $(OBJECTS) -o $(PROJECT_NAME)

list_graph.o: list_graph.c list_graph.h
	$(EXEC) $(CFLAGS) -c list_graph.c

list.o: list.c list.h
	$(EXEC) $(CFLAGS) -c list.c

queue.o: queue.c queue.h
	$(EXEC) $(CFLAGS) -c queue.c

main.o: main.c 
	$(EXEC) $(CFLAGS) -c main.c
