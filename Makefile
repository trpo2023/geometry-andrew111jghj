TARGET = main
CC = g++
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD
WAY_SOURCE_CODE_FILES = src/libgeometry/
WAY_SOURCE_MAIN = src/geometry/
WAY_OBJECT_FILES = obj/src/geometry/
WAY_OBJECT_LIB = obj/src/libgeometry/
WAY_TARGET = bin/

SOURCE_CODE_FILES = $(wildcard $(WAY_SOURCE_CODE_FILES)*.cpp)
OBJECT_CODE_FILES = $(patsubst $(WAY_SOURCE_CODE_FILES)%.cpp, $(WAY_OBJECT_FILES)%.o, $(SOURCE_CODE_FILES))
SOURCE_MAIN = $(WAY_SOURCE_MAIN)main.cpp

$(WAY_TARGET)$(TARGET) : $(WAY_OBJECT_FILES)main.o $(WAY_OBJECT_LIB)libmy.a
	$(CC) $(CFLAGS) $(OBJECT_CODE_FILES) $(WAY_OBJECT_FILES)main.o -L$(WAY_OBJECT_LIB) -lmy -o $(WAY_TARGET)$(TARGET)

$(WAY_OBJECT_FILES)%.o : $(WAY_SOURCE_CODE_FILES)%.cpp
	$(CC) -c -I$(WAY_SOURCE_CODE_FILES) $(CFLAGS) $(CPPFLAGS) $< -o $@

$(WAY_OBJECT_FILES)main.o : $(WAY_SOURCE_MAIN)main.cpp
	$(CC) -c -I$(WAY_SOURCE_CODE_FILES) $(CFLAGS) $(CPPFLAGS) $< -o $@

$(WAY_OBJECT_LIB)libmy.a : $(OBJECT_CODE_FILES)
	ar rcs $@ $^
run :
	./$(WAY_TARGET)$(TARGET)

clean : 
	rm $(WAY_TARGET)$(TARGET) $(WAY_OBJECT_FILES)*.[od]

.PHONY: clean run

-include $(wildcard $(WAY_OBJECT_FILES)*.d)