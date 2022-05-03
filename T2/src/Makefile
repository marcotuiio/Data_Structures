EXEC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g -Wall
PROJECT_NAME = ted

clear: 
	rm *.o
	rm $(PROJECT_NAME)

$(PROJECT_NAME): main.o system.o paths.o
	$(EXEC) $(CFLAGS) main.o system.o paths.o -o $(PROJECT_NAME)

# svg.o: svg.c svg.h 
# 	$(EXEC) $(CFLAGS) -c svg.c

# geo.o: geo.c geo.h 
# 	$(EXEC) $(CFLAGS) -c geo.c

# qry.o: qry.c qry.h
# 	$(EXEC) $(CFLAGS) -c qry.c	

system.o: system.c system.h
	$(EXEC) $(CFLAGS) -c system.c

paths.o: paths.c paths.h
	$(EXEC) $(CFLAGS) -c paths.c	

main.o: main.c system.h paths.h
	$(EXEC) $(CFLAGS) -c main.c