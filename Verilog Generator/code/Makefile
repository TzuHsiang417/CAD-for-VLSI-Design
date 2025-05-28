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
OBJECTS = $(BUILD_PATH)/Verilog_Generator.exe

# Compiler flags
CXXFLAG = -O3 -Wall
INCLUDE = -I$(SRC_PATH) 

# Make-command list
.PHONY: clean

# Target: Dependencies
# 	Shell-command

main.out: main.cpp
	$(CC) $(C17) -o $(OBJECTS) main.cpp

clean:
	@echo "Removing objects"
	@echo "Removing executable file"
	del main.out *.o *.exe