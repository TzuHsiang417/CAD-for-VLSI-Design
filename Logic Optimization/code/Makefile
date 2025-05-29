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
OBJECTS = $(BUILD_PATH)/PA3_107501019.exe

# Compiler flags
CXXFLAG = -O3 -Wall
INCLUDE = -I$(SRC_PATH) 

# Make-command list
.PHONY: clean

# Target: Dependencies
# 	Shell-command

main.out: main.o QM.o covering.o readfile.o
	$(CC) $(C17) -o $(OBJECTS) main.o QM.o covering.o readfile.o

main.o: main.cpp QM.o covering.o readfile.o
	$(CC) $(C17) -c main.cpp

covering.o: covering.cpp logicOpt.h
	$(CC) $(C17) -c covering.cpp

QM.o: QM.cpp logicOpt.h
	$(CC) $(C17) -c QM.cpp

readfile.o: readfile.cpp logicOpt.h
	$(CC) $(C17) -c readfile.cpp

clean:
	@echo "Removing objects"
	@echo "Removing executable file"
	del main.out *.o *.exe
