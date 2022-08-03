EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
PROJECT_NAME = teste

clear: 
	rm *.o
	rm $(PROJECT_NAME)

$(PROJECT_NAME): main.o avl_tree.o 
	$(EXEC) $(CFLAGS) main.o avl_tree.o -o $(PROJECT_NAME)

tree.o: avl_tree.c avl_tree.h
	$(EXEC) $(CFLAGS) -c avl_tree.c

main.o: main.c 
	$(EXEC) $(CFLAGS) -c main.c
