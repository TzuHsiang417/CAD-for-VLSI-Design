#ifndef _BLOCK_H
#define _BLOCK_H

#include <vector>
#include <string>

using namespace std;

class block{    //block in NPE
    string name;
    vector<pair<float, float> > WidthHeight;
    friend class FloorPlanning;

    public:
        block(string a,vector<pair<float,float> >b):name(a),WidthHeight(b){}    //constructor
};

#endif