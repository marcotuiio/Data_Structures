EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g
PROJECT_NAME = ted

clear: 
	rm *.o
	rm $(PROJECT_NAME)

$(PROJECT_NAME): main.o lista2.o fila_circ.o
	$(EXEC) $(CFLAGS) main.o lista2.o fila_circ.o -o $(PROJECT_NAME)

lista2.o: lista2.c lista2.h
	$(EXEC) $(CFLAGS) -c lista2.c

fila_circ.o: fila_circ.c fila_circ.h
	$(EXEC) $(CFLAGS) -c fila_.c	