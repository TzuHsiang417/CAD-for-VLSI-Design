# Compiler
CC = g++
C17 = -std=c++17

# Path
SRC_PATH = .
BUILD_PATH = .

# Executable 
EXE = go

# Source 
SOURCES = $(SRC_PATH)/main.cpp  
OBJECTS = $(BUILD_PATH)/PA2_107501019.exe

# Compiler flags
CXXFLAG = -O3 -Wall
INCLUDE = -I$(SRC_PATH) 

# Make-command list
.PHONY: clean

# Target: Dependencies
# 	Shell-command

main.out: main.o arrangement.o scheduling.o readfile.o
	$(CC) $(C17) -o $(OBJECTS) main.o arrangement.o scheduling.o readfile.o

main.o: main.cpp arrangement.o scheduling.o readfile.o
	$(CC) $(C17) -c main.cpp

arrangement.o: arrangement.cpp scheduling.h
	$(CC) $(C17) -c arrangement.cpp

scheduling.o: scheduling.cpp scheduling.h
	$(CC) $(C17) -c scheduling.cpp

readfile.o: readfile.cpp scheduling.h
	$(CC) $(C17) -c readfile.cpp

clean:
	@echo "Removing objects"
	@echo "Removing executable file"
	del main.out *.o *.exe
