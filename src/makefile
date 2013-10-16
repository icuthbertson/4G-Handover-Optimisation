CC=g++
CFLAGS=-I.
DEPS = basestation.hpp mobile.hpp
OBJ = simulation.cpp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

simulation: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)
