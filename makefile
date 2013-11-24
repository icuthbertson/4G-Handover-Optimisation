CC = g++
CFLAGS = -Wall -pedantic -g
LDFLAGS = -lm

simulation.o :
	${CC} ${CFLAGS} -c src/simulation.cpp
	
mobile.o :
	${CC} ${CFLAGS} -c src/mobile.cpp

basestation.o :
	${CC} ${CFLAGS} -c src/basestation.cpp

event_handler.o :
	${CC} ${CFLAGS} -c src/event_handler.cpp
	
payloadType.o :
	${CC} ${CFLAGS} -c src/payloadType.cpp

scheduler.o :
	${CC} ${CFLAGS} -c src/scheduler.cpp

all : event_handler.o payloadType.o  scheduler.o basestation.o mobile.o simulation.o
	${CC} ${CFLAGS} basestation.o mobile.o simulation.o event_handler.o payloadType.o scheduler.o ${LDFLAGS} -o bin/simulation
	mv event_handler.o payloadType.o scheduler.o basestation.o mobile.o simulation.o bin
	rm -rf *.o
	
clean :
	rm -rf *.o bin/*.o bin/simulation