# Assignment 4 Slicing Floorplanning
To minimize the chip placement area, we aim to develop an algorithm that places all blocks within the smallest possible bounding box while reducing dead space as much as possible. The goal of this programming assignment is to optimize the placement of given soft block modules by minimizing the overall area using the Simulated Annealing (SA) approach based on the Wong-Liu algorithm and the Normalized Polish Expression (NPE), while ensuring that no overlapping occurs.
  
For more details, refer to: [2021Spring_EE6094_CAD_PA4_Floorplanning.pdf](2021Spring_EE6094_CAD_PA4_Floorplanning.pdf)

## Program Structure and Algorithms
<img src="https://github.com/TzuHsiang417/CAD-for-VLSI-Design/blob/main/Slicing%20Floorplanning/picture/Program_Structure.jpg" width="50%">

## Compilation
Run the following command to compile the project:
```sh
make
```

## Clean
The following command removes all files generated during the compilation process:
```sh
make clean
```

## How to excecute
Run the program: 
```sh
./PA4_107501019.exe input.txt output_file
```

## Checker
```sh
./PA4_CHECKER.out input.txt output_file
```
Before you use this checker, you have to type `chmod 755 PA4_checker.out` in your command line. And you can use this checker.  
If your program is correct, you will get the following prompt message:
```
Expression is correct!!
Module size is correct.
Overlapping check is correct.
All correct! Will done.
```
On the contract, if your program has some mistake, you will get which state is incorrect. 
For example, if your normalized polish expression is incorrect, you will get `Expression has some mistake.` and so on.

## Reports
Execution Results and Report: 
[PA4_107501019_report.pdf](PA4_107501019_report.pdf)
