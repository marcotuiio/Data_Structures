EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
PROJECT_NAME = teste

clear: 
	rm *.o
	rm $(PROJECT_NAME)

$(PROJECT_NAME): main.o hash_table.o
	$(EXEC) $(CFLAGS) main.o hash_table.o -o $(PROJECT_NAME)

# avl_tree.o: avl_tree.c avl_tree.h
# 	$(EXEC) $(CFLAGS) -c avl_tree.c

# hash_table.o: hash_table_enderecamento.c hash_table.h
# 	$(EXEC) $(CFLAGS) -c hash_table_enderecamento.c

hash_table.o: hash_table_lists.c hash_table.h
	$(EXEC) $(CFLAGS) -c hash_table_lists.c

main.o: main.c 
	$(EXEC) $(CFLAGS) -c main.c
