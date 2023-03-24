.PHONY: clean run
TARGET = main
CC = g++
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD
WAY_SOURCE = ./src/
WAY_OBJECT = ./obj/

SOURCE = $(wildcard $(WAY_SOURCE)*.cpp)
OBJECT = $(patsubst $(WAY_SOURCE)%.cpp, $(WAY_OBJECT)%.o, $(SOURCE))

$(TARGET) : $(WAY_OBJECT)main.o $(WAY_OBJECT)libcompute.a
	$(CC) $(CFLAGS) $(OBJECT) -L$(WAY_OBJECT) -lcompute -o $(TARGET)

$(WAY_OBJECT)%.o : $(WAY_SOURCE)%.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(WAY_OBJECT)libcompute.a : $(WAY_OBJECT)compute.o
	ar rcs $@ $^
run :
	./main

clean : 
	rm $(TARGET) $(WAY_OBJECT)*.o $(WAY_OBJECT)*.d $(WAY_OBJECT)*.a

-include $(WAY_OBJECT)main.d $(WAY_OBJECT)compute.d