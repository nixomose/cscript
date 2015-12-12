
CC=g++
CFLAGS=-c -Wall -O2
LDFLAGS=
SOURCES=cscript.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TARGET=cscript
BINDIR=/usr/bin

all: bin $(SOURCES) $(TARGET)
    
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
        
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@    

bin:
	mkdir bin

install: all
	install -D $(TARGET) $(BINDIR)/$(TARGET)

uninstall:
	-rm $(BINDIR)/$(TARGET)

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)
