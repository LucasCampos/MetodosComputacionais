OPTFLAGS    = -fast
CC          = c++
MAKE        = make
SHELL       = /bin/sh

FOLDERS = includes
LIBS = -lglfw# -fopenmp
FLAGS = -O3

EXECS = latticeGas
SOURCES = latticeGas.cpp
HEADERS = includes/cell.hpp includes/lattice.hpp includes/rules.hpp
OBJECTS = $(SOURCES:.cpp=.o)

$(EXECS): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LIBS) $(FLAGS) -I $(FOLDERS) 

.cpp.o: $(HEADERS)
	$(CC) -c $(SOURCES) $(LIBS) $(FLAGS) -I $(FOLDERS) 

clean:
	/bin/rm -f *.o *.mod $(EXECS) *.gnu *.sh *.gif

profile: $(EXECS)
	./$(EXECS)
	gprof $(EXECS) -b
run: $(EXECS)
	./$(EXECS) 
