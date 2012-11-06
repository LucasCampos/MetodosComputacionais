OPTFLAGS    = -fast
CC          = nvcc
MAKE        = make
SHELL       = /bin/sh

FOLDERS = includes
LIBS = -lGLEW -lglfw
FLAGS =  -O3 -lineinfo -arch="sm_21"

EXECS = latticeGas
SOURCES = latticeGas.cu
HEADERS = includes/cell.hpp includes/lattice.hpp includes/rules.hpp
OBJECTS = $(SOURCES:.cpp=.o)

$(EXECS): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LIBS) $(FLAGS) -I $(FOLDERS) 

.cpp.o: $(HEADERS)
	$(CC) -c $(SOURCES) $(LIBS) $(FLAGS) -I $(FOLDERS) 

clean:
	/bin/rm -f *.o *.mod $(EXECS) *.gnu *.sh *.gif

debug: $(EXECS)
	optirun $(EXECS)

run: $(EXECS)
	optirun ./$(EXECS) 
