EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
PROJECT_NAME = ted

clear: 
	rm *.o
	rm $(PROJECT_NAME)

$(PROJECT_NAME): main.o svg.o geo.o qry.o system.o paths.o rectangle.o circle.o line.o text.o list.o tree.o
	$(EXEC) $(CFLAGS) main.o svg.o geo.o qry.o system.o paths.o rectangle.o circle.o line.o text.o list.o tree.o -o $(PROJECT_NAME)

svg.o: svg.c svg.h 
	$(EXEC) $(CFLAGS) -c svg.c

geo.o: geo.c geo.h 
	$(EXEC) $(CFLAGS) -c geo.c

qry.o: qry.c qry.h
	$(EXEC) $(CFLAGS) -c qry.c	

system.o: system.c system.h
	$(EXEC) $(CFLAGS) -c system.c

paths.o: paths.c paths.h
	$(EXEC) $(CFLAGS) -c paths.c

rectangle.o: rectangle.c rectangle.h 
	$(EXEC)	$(CFLAGS) -c rectangle.c

circle.o: circle.c circle.h 
	$(EXEC)	$(CFLAGS) -c circle.c			

line.o: line.c line.h 
	$(EXEC)	$(CFLAGS) -c line.c

text.o: text.c text.h 
	$(EXEC)	$(CFLAGS) -c text.c
	
tree.o: tree.c tree.h 
	$(EXEC)	$(CFLAGS) -c tree.c

list.o: list.c list.h 
	$(EXEC)	$(CFLAGS) -c list.c

main.o: main.c system.h paths.h
	$(EXEC) $(CFLAGS) -c main.c