CC=g++
CFLAGS=-c -Wall -I/opt/local/include/
LDFLAGS=-L/opt/local/lib -lfann
LDLIBS=
SOURCES=main.cpp control/cli.cpp control/api.cpp lib/log.cpp lib/control.cpp lib/singleton.cpp lib/fs.cpp lib/helper.cpp model/ann.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=fannd

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)
	rm $(EXECUTABLE)