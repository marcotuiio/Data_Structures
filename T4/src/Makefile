EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
PROJECT_NAME = ted
OBJETCS = main.o geo.o list.o paths.o system.o infos.o digraph.o queue.o
ALUNO = marcotab

clear:
	rm *.o
	rm $(PROJECT_NAME)

pack: $(PROJECT_NAME)
	rm -f ../$(ALUNO).zip
	echo $(ALUNO)
	date >> .entrega
	cd ..; zip $(ALUNO).zip -r src/*.c src/*.h src/Makefile LEIA-ME.txt .entrega

$(PROJECT_NAME): $(OBJETCS) 
	$(EXEC) $(CFLAGS) $(OBJETCS) -o $(PROJECT_NAME) -lm

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

infos.o: infos.c infos.h
	$(EXEC) $(CFLAGS) -c infos.c

digraph.o: digraph.c digraph.h
	$(EXEC) $(CFLAGS) -c digraph.c

svg.o: svg.c svg.h
	$(EXEC) $(CFLAGS) -c svg.c

system.o: system.c system.h
	$(EXEC) $(CFLAGS) -c system.c

queue.o: queue.c queue.h
	$(EXEC) $(CFLAGS) -c queue.c

priority_queue.o: priority_queue.c priority_queue.h
	$(EXEC) $(CFLAGS) -c priority_queue.c