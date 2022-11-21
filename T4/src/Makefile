EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
PROJECT_NAME = t2
OBJETCS = main.o digraph.o dijkstra.o geo.o infos.o list.o paths.o priority_queue.o queue.o qry.o rb_tree.o svg.o system.o via.o
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

digraph.o: digraph.c digraph.h
	$(EXEC) $(CFLAGS) -c digraph.c

dijkstra.o: dijkstra.c dijkstra.h
	$(EXEC) $(CFLAGS) -c dijkstra.c

geo.o: geo.c geo.h
	$(EXEC) $(CFLAGS) -c geo.c

infos.o: infos.c infos.h
	$(EXEC) $(CFLAGS) -c infos.c

list.o: list.c list.h
	$(EXEC) $(CFLAGS) -c list.c

paths.o: paths.c paths.h
	$(EXEC) $(CFLAGS) -c paths.c

priority_queue.o: priority_queue.c priority_queue.h
	$(EXEC) $(CFLAGS) -c priority_queue.c

queue.o: queue.c queue.h
	$(EXEC) $(CFLAGS) -c queue.c

qry.o: qry.c qry.h
	$(EXEC) $(CFLAGS) -c qry.c

rb_tree.o: rb_tree.c rb_tree.h
	$(EXEC) $(CFLAGS) -c rb_tree.c

svg.o: svg.c svg.h
	$(EXEC) $(CFLAGS) -c svg.c

system.o: system.c system.h
	$(EXEC) $(CFLAGS) -c system.c

via.o: via.c via.h
	$(EXEC) $(CFLAGS) -c via.c

main.o: main.c
	$(EXEC) $(CFLAGS) -c main.c