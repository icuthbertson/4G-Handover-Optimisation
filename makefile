CC = g++
CFLAGS = -g
LDFLAGS = -lm

simulation.o :
	${CC} ${CFLAGS} -c src/simulation.cpp
	
mobile.o :
	${CC} ${CFLAGS} -c src/mobile.cpp

basestation.o :
	${CC} ${CFLAGS} -c src/basestation.cpp

q_learning.o :
	${CC} ${CFLAGS} -c src/q_learning.cpp

simple_learning.o :
	${CC} ${CFLAGS} -c src/simple_learning.cpp

event_handler.o :
	${CC} ${CFLAGS} -c src/event_handler.cpp
	
payloadType.o :
	${CC} ${CFLAGS} -c src/payloadType.cpp

scheduler.o :
	${CC} ${CFLAGS} -c src/scheduler.cpp

event.o :
	${CC} ${CFLAGS} -c src/event.cpp

all : event.o event_handler.o payloadType.o scheduler.o simple_learning.o q_learning.o basestation.o mobile.o simulation.o
	${CC} ${CFLAGS} simple_learning.o q_learning.o basestation.o mobile.o simulation.o event_handler.o payloadType.o scheduler.o event.o ${LDFLAGS} -o bin/simulation
	mv event_handler.o payloadType.o scheduler.o simple_learning.o q_learning.o basestation.o mobile.o simulation.o bin
	rm -rf *.o
	
clean :
	rm -rf *.o bin/*.o bin/simulation