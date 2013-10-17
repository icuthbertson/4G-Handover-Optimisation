CC=g++
CFLAGS=-I.
DEPS = basestation.hpp mobile.hpp basestation.cpp mobile.cpp 
OBJ = simulation.cpp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

simulation: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)
