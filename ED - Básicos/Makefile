EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
PROJECT_NAME = treeTest

clear: 
	rm *.o
	rm $(PROJECT_NAME)

$(PROJECT_NAME): testetree.o tree.o 
	$(EXEC) $(CFLAGS) testetree.o tree.o -o $(PROJECT_NAME)

tree.o: tree.c tree.h
	$(EXEC) $(CFLAGS) -c tree.c

testetree.o: main.c 
	$(EXEC) $(CFLAGS) -c testetree.c
