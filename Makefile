SOURCES=$(wildcard src/**/*.c src/*.c)
EXECUTABLE=lottery
TARGET=bin
CFLAGS= -Wall -Wextra


all: clean $(EXECUTABLE)

build:
	$(CC) -c $(SOURCES) 
	mv *.o src/ 
	cp src/execution.conf $(TARGET)

$(EXECUTABLE): $(TARGET) build
	$(CC) $(SOURCES) -o $(TARGET)/$(EXECUTABLE) -lm

$(TARGET):
	mkdir bin/

clean:
	rm -f $(OBJECTS)  
	rm -rf target/
