EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
PROJECT_NAME = ted

clear: 
	rm *.o
	rm $(PROJECT_NAME)

$(PROJECT_NAME): main.o shapes.o avl_tree.o svg.o geo.o system.o paths.o 
	$(EXEC) $(CFLAGS) main.o shapes.o avl_tree.o svg.o geo.o system.o paths.o -o $(PROJECT_NAME) -lm

svg.o: svg.c svg.h 
	$(EXEC) $(CFLAGS) -c svg.c

geo.o: geo.c geo.h 
	$(EXEC) $(CFLAGS) -c geo.c

shapes.o: shapes.c shapes.h 
	$(EXEC)	$(CFLAGS) -c shapes.c
	
avl_tree.o: avl_tree.c avl_tree.h 
	$(EXEC)	$(CFLAGS) -c avl_tree.c

# qry.o: qry.c qry.h
# 	$(EXEC) $(CFLAGS) -c qry.c	

system.o: system.c system.h
	$(EXEC) $(CFLAGS) -c system.c

paths.o: paths.c paths.h
	$(EXEC) $(CFLAGS) -c paths.c

main.o: main.c
	$(EXEC) $(CFLAGS) -c main.c