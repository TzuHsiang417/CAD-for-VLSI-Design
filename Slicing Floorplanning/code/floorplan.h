#ifndef _FLOORPLAN_H
#define _FLOORPLAN_H

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <map>
#include <stack>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include "parameter.h"
#include "block.h"

using namespace std;

template<typename T>
void FreeVector(vector<T> &vt)
{
    vector<T> vt_tmp;
    vt_tmp.swap(vt);
}

class FloorPlanning{    //floorplanning
    map<string, float> module;  

    public:
        map<string, pair<float, float> > F_WidthHeight; //final width and height
        map<string, pair<float, float> > F_coordinate;  //final coordinate
        
        FloorPlanning(map<string, float>m):module(m){}  //constructor
        void InitialNPE(vector<string>&npe);
        vector<block *>createNPE_Block(vector<string>&npe);
        void Combination(block*operand1, block*operand2, block*operator1);
        float Cost(vector<string>&npe);
        bool Check_consecutive(vector<string>&npe);
        bool Check_ballot(vector<string>&npe);
        void M1(vector<string>&npe);
        void M2(vector<string>&npe);
        void M3(vector<string>&npe);
        void Wong_Liu_ALGO(vector<string>&npe);
        void Create_Information(vector<string>&npe);
        void printNPE(vector<string>&npe);
};


#endif