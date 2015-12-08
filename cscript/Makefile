

CC=g++
CFLAGS=-c -Wall -O2
LDFLAGS=
SOURCES=cscript.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bin/cscript

all: bin $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
        
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@    
    
bin:
	mkdir bin
