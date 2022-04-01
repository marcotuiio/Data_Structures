EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g
PROJECT_NAME = ted

clear: 
	rm *.o
	rm $(PROJECT_NAME)

$(PROJECT_NAME): main.o system.o files.o geo.o list.o rectangle.o circle.o line.o text.o svg.o
	$(EXEC) $(CFLAGS) main.o system.o files.o geo.o list.o rectangle.o circle.o line.o text.o svg.o -o $(PROJECT_NAME)

svg.o: svg.c svg.h
	$(EXEC) $(CFLAGS) -c svg.c

list.o: list.c list.h
	$(EXEC) $(CFLAGS) -c list.c

rectangle.o: rectangle.c rectangle.h
	$(EXEC)	$(CFLAGS) -c rectangle.c

circle.o: circle.c circle.h
	$(EXEC)	$(CFLAGS) -c circle.c			

line.o: line.c line.h
	$(EXEC)	$(CFLAGS) -c line.c

text.o: text.c text.h
	$(EXEC)	$(CFLAGS) -c text.c

geo.o: geo.c geo.h list.h
	$(EXEC) $(CFLAGS) -c geo.c

files.o: files.c files.h
	$(EXEC) $(CFLAGS) -c files.c

system.o: system.c system.h
	$(EXEC) $(CFLAGS) -c system.c

main.o: main.c system.h files.h geo.h
	$(EXEC) $(CFLAGS) -c main.c