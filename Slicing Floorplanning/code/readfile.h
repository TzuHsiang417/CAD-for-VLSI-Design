#ifndef _READFILE_H
#define _READFILE_H

#include "floorplan.h"

bool ReadFile(char *argv, int *num_module, map<string, float> &module);
void Create_file(char *argv, int num_module, FloorPlanning *FP, vector<string> &npe);

#endif