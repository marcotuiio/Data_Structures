EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
PROJECT_NAME = ted

clear:
	rm *.o
	rm $(PROJECT_NAME)

$(PROJECT_NAME): main.o geo.o list.o paths.o qry.o shapes.o srb_tree.o svg.o system.o 
	$(EXEC) $(CFLAGS) main.o geo.o list.o paths.o qry.o shapes.o srb_tree.o svg.o system.o -o $(PROJECT_NAME) -lm

main.o: main.c
	$(EXEC) $(CFLAGS) -c main.c

geo.o: geo.c geo.h
	$(EXEC) $(CFLAGS) -c geo.c

list.o: list.c list.h
	$(EXEC) $(CFLAGS) -c list.c

paths.o: paths.c paths.h
	$(EXEC) $(CFLAGS) -c paths.c

qry.o: qry.c qry.h
	$(EXEC) $(CFLAGS) -c qry.c

shapes.o: shapes.c shapes.h
	$(EXEC) $(CFLAGS) -c shapes.c

srb_tree.o: srb_tree.c srb_tree.h
	$(EXEC) $(CFLAGS) -c srb_tree.c

svg.o: svg.c svg.h
	$(EXEC) $(CFLAGS) -c svg.c

system.o: system.c system.h
	$(EXEC) $(CFLAGS) -c system.c
