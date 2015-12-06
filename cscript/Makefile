

CC=g++
CFLAGS=-c -Wall
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
