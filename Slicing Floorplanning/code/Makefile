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
OBJECTS = $(BUILD_PATH)/PA4_107501019.exe

# Compiler flags
CXXFLAG = -O3 -Wall
INCLUDE = -I$(SRC_PATH) 

# Make-command list
.PHONY: clean

# Target: Dependencies
# 	Shell-command

main.out: main.o readfile.o cost.o floorplan.o move.o SA.o
	$(CC) $(C17) -o $(OBJECTS) main.o readfile.o cost.o floorplan.o move.o SA.o

main.o: main.cpp readfile.o cost.o floorplan.o move.o SA.o
	$(CC) $(C17) -c main.cpp

readfile.o: readfile.cpp floorplan.h parameter.h
	$(CC) $(C17) -c readfile.cpp

floorplan.o: floorplan.cpp floorplan.h parameter.h
	$(CC) $(C17) -c floorplan.cpp

move.o: move.cpp floorplan.h parameter.h
	$(CC) $(C17) -c move.cpp

cost.o: cost.cpp floorplan.h parameter.h
	$(CC) $(C17) -c cost.cpp

SA.o: SA.cpp floorplan.h parameter.h
	$(CC) $(C17) -c SA.cpp

clean:
	@echo "Removing objects"
	@echo "Removing executable file"
	del main.out *.o *.exe
