TARGET = main
TARGET_TEST = main_test
std = c++11
CC = g++ 
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD
WAY_SOURCE_CODE_FILES = src/libgeometry/
WAY_SOURCE_MAIN = src/geometry/
WAY_OBJECT_FILES = obj/src/geometry/
WAY_OBJECT_LIB = obj/src/libgeometry/
WAY_TARGET = bin/
WAY_TARGET_TEST = bin/
WAY_OBJECT_TEST = obj/test/
WAY_SOURCE_CODE_FILE_TEST = test/


SOURCE_CODE_FILES = $(wildcard $(WAY_SOURCE_CODE_FILES)*.cpp)
OBJECT_CODE_FILES = $(patsubst $(WAY_SOURCE_CODE_FILES)%.cpp, $(WAY_OBJECT_FILES)%.o, $(SOURCE_CODE_FILES))
SOURCE_MAIN = $(WAY_SOURCE_MAIN)main.cpp

SOURCE_CODE_FILE_TEST = $(wildcard $(WAY_SOURCE_CODE_FILE_TEST)*.cpp)
OBJECT_CODE_FILE_TEST = $(patsubst $(WAY_SOURCE_CODE_FILE_TEST)%.cpp, $(WAY_OBJECT_TEST)%.o, $(SOURCE_CODE_FILE_TEST))

all: clang $(WAY_TARGET_TEST)$(TARGET_TEST) test $(WAY_TARGET)$(TARGET) run clean 

#main
$(WAY_TARGET)$(TARGET) : $(WAY_OBJECT_FILES)main.o $(WAY_OBJECT_LIB)libmy.a
	$(CC) $(CFLAGS) $(OBJECT_CODE_FILES) $(WAY_OBJECT_FILES)main.o -L$(WAY_OBJECT_LIB) -lmy -o $(WAY_TARGET)$(TARGET)

$(WAY_OBJECT_FILES)%.o : $(WAY_SOURCE_CODE_FILES)%.cpp
	$(CC) -c -I$(WAY_SOURCE_CODE_FILES) $(CFLAGS) $(CPPFLAGS) $< -o $@

$(WAY_OBJECT_FILES)main.o : $(WAY_SOURCE_MAIN)main.cpp
	$(CC) -c -I$(WAY_SOURCE_CODE_FILES) $(CFLAGS) $(CPPFLAGS) $< -o $@
###

#Lib
$(WAY_OBJECT_LIB)libmy.a : $(OBJECT_CODE_FILES)
	ar rcs $@ $^
###

#test
$(WAY_TARGET_TEST)$(TARGET_TEST) : $(OBJECT_CODE_FILE_TEST) $(WAY_OBJECT_LIB)libmy.a
	$(CC) $(CFLAGS) $(OBJECT_CODE_FILE_TEST) $(WAY_OBJECT_LIB)libmy.a -o $(WAY_TARGET_TEST)$(TARGET_TEST)

$(WAY_OBJECT_TEST)%.o : $(WAY_SOURCE_CODE_FILE_TEST)%.cpp
	$(CC) -c $(CPPFLAGS) -I$(WAY_SOURCE_CODE_FILES) -I$(WAY_SOURCE_CODE_FILE_TEST) -I thirdparty/ $< -w -o $@
###

clang :
	clang-format -i --verbose $(SOURCE_CODE_FILES) $(WAY_SOURCE_MAIN)main.cpp

run :
	./$(WAY_TARGET)$(TARGET)

test :
	./$(WAY_TARGET_TEST)$(TARGET_TEST)

clean : 
	rm $(WAY_TARGET)$(TARGET) $(WAY_OBJECT_FILES)*.[od] $(WAY_OBJECT_LIB)*.a $(WAY_OBJECT_TEST)*.[od] $(WAY_TARGET_TEST)$(TARGET_TEST)

.PHONY: clean run test all

-include $(wildcard $(WAY_OBJECT_FILES)*.d) $(wildcard $(WAY_OBJECT_TEST)*.d)