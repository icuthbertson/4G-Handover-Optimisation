CC=g++
CFLAGS=-I. -I$SYSTEMC_HOME/include -L. -LSYSTEMC_HOME/lib-linux64
LDFLAGS=-lsystemc -lm
DEPS = basestation.hpp mobile.hpp
OBJ = simulation.cpp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

simulation: $(OBJ)
	g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -o out simulation.cpp basestation.hpp mobile.hpp -lsystemc -lm


