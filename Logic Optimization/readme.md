# Assignment 3 Logic Optimization
The objective of logic optimization is to improve a given combinational circuit in terms of performance or area, in order to meet design constraints. This process facilitates effective technology mapping by transforming Boolean networks—often in a non-circuit form—into optimized circuit implementations that satisfy specified cost and constraint requirements.  
  
For more details, refer to: [2021Spring_EE6094_CAD_PA3_Logic_Opt.pdf](2021Spring_EE6094_CAD_PA3_Logic_Opt.pdf)

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
PA3_107501019.exe testX.eqn output_file
```

## Checker
#### Step 1: 
Download the entire ABC tool package from:
https://github.com/berkeley-abc/abc

#### Step 2:  
After extracting the files, place the folder on the workstation.
```sh
cd abc-master/
```
Navigate into the abc-master directory and run the make command.
```sh
make
```
You will see the program begin compiling various modules. It's normal to encounter a few "Permission denied" messages initially.

#### Step 3: 
Once the compilation is complete, you can launch the ABC program by running the corresponding executable.
```sh
./abc
```
To perform functional equivalence checking, place the two circuits to be compared on the workstation and use the cec command within ABC.
```sh
cec INPUT_FILE OUTPUT_FILE
```
If the result indicates equivalence, it means the two Boolean functions are functionally equivalent.

## Reports
Execution Results and Report: 
[PA3_107501019_report.pdf](PA3_107501019_report.pdf)
