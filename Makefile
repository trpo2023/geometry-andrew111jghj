CC = g++
CFLAGS = -Wall
TARGET = main
SOURCES = main.cpp

all: clean $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) geometry.txt

clean:
	rm -f $(TARGET); clear;