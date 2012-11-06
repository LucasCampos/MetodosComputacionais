OPTFLAGS    = -fast
CC          = g++
MAKE        = make
SHELL       = /bin/sh

FOLDERS = ../includes
LIBS = -lglfw 
FLAGS = -O3

EXECS = miniSolar
SOURCES = miniSolar.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(EXECS): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LIBS) $(FLAGS) 

.cpp.o: 
	$(CC) -c $(SOURCES) $(LIBS) $(FLAGS)

clean:
	/bin/rm -f *.o *.mod $(EXECS) *.gnu *.sh *.gif
run: $(EXECS)
	./$(EXECS) 
