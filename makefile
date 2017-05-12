CC = g++
CFLAGS = -g -Wall
SOURCES = *.cpp
OBJECTS=
EXECUTABLE = run
all: $(SOURCES) $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(SOURCES) $(OBJECTS) -o $@
.cpp.o:
	$(CC) $(CFLAGS) $<-o $@
