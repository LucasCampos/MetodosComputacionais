OPTFLAGS    = -fast
CC          = g++
MAKE        = make
SHELL       = /bin/sh

FOLDERS = ../includes
LIBS = -lglfw -lGL
FLAGS = -O3

EXECS = collision
SOURCES = collision.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(EXECS): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LIBS) $(FLAGS)

.cpp.o: 
	$(CC) -c $(SOURCES) $(LIBS) $(FLAGS)

clean:
	/bin/rm -f *.o *.mod $(EXECS) *.gif
run: $(EXECS)
	./$(EXECS) 
	gnuplot plot.gnu -p
