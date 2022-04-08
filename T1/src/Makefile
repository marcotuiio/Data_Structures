EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g
PROJECT_NAME = ted

clear: 
	rm *.o
	rm $(PROJECT_NAME)

$(PROJECT_NAME): main.o system.o geo.o qry.o list.o fila_circ.o rectangle.o circle.o line.o text.o svg.o
	$(EXEC) $(CFLAGS) main.o system.o geo.o qry.o list.o fila_circ.o rectangle.o circle.o line.o text.o svg.o -o $(PROJECT_NAME)

svg.o: svg.c svg.h list.h
	$(EXEC) $(CFLAGS) -c svg.c

list.o: list.c list.h
	$(EXEC) $(CFLAGS) -c list.c

fila_circ.o: fila_circ.c fila_circ.h
	$(EXEC) $(CFLAGS) -c fila_circ.c	

rectangle.o: rectangle.c rectangle.h list.h
	$(EXEC)	$(CFLAGS) -c rectangle.c

circle.o: circle.c circle.h list.h
	$(EXEC)	$(CFLAGS) -c circle.c			

line.o: line.c line.h list.h
	$(EXEC)	$(CFLAGS) -c line.c

text.o: text.c text.h list.h
	$(EXEC)	$(CFLAGS) -c text.c

geo.o: geo.c geo.h list.h rectangle.h circle.h line.h text.h svg.h
	$(EXEC) $(CFLAGS) -c geo.c

qry.o: qry.c qry.h
	$(EXEC) $(CFLAGS) -c qry.c	

system.o: system.c system.h
	$(EXEC) $(CFLAGS) -c system.c

main.o: main.c system.h geo.h 
	$(EXEC) $(CFLAGS) -c main.c