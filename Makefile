SOURCES=$(wildcard src/**/*.c src/*.c)
EXECUTABLE=lottery
TARGET=bin
CFLAGS= 
LDLIBS= `pkg-config --libs gtk+-3.0` 
CPPFLAGS= `pkg-config --cflags gtk+-3.0`

#gcc `pkg-config --cflags gtk+-3.0` -o main2  main2.c `pkg-config --libs gtk+-3.0`

all: clean $(EXECUTABLE)

build:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(SOURCES) 
	mv *.o src/ 
	cp src/execution.conf $(TARGET)
	cp src/ui/builder.ui $(TARGET)

$(EXECUTABLE): $(TARGET) build
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SOURCES) -o $(TARGET)/$(EXECUTABLE) -lm $(LDLIBS)

$(TARGET):
	mkdir bin/

clean:
	rm -f $(OBJECTS)  
	rm -rf target/