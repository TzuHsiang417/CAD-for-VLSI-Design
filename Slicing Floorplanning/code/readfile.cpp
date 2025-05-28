#include "readfile.h"
#include <fstream>

bool ReadFile(char *argv, int *num_module, map<string, float> &module)  //read input file
{
    ifstream ifile(argv, ios::in);

    if(!ifile)
    {
        ifile.close();
        return 0;
    }
    else
    {
        ifile >> *num_module;
        string name;
        int area;

        while(ifile >> name >> area)
        {
            module[name] = area;
        }
        ifile.close();
        return 1;
    }
}

void Create_file(char *argv, int num_module, FloorPlanning *FP, vector<string> &npe)    //creat output file
{
    ofstream ofile(argv, ios::out);
    if(ofile.is_open())
    {
        float total_width = 0.0, total_height = 0.0;
        for(int i=0; i<num_module; i++)
        {
            string str_i;
            stringstream ss;
            ss << i;
            ss >> str_i;
            pair<float, float> a = FP->F_WidthHeight[str_i];
            pair<float, float> b = FP->F_coordinate[str_i];
            if(a.first+b.first > total_width)
                total_width = floor(a.first*1000)/1000 + floor(b.first*1000)/1000;
            if(a.second+b.second > total_height)
                total_height = floor(a.second*1000)/1000 + floor(b.second*1000)/1000;
        }
        ofile << fixed << setprecision(3) << total_width << " " << total_height << " " << total_width*total_height << endl;
        for(int i=0; i<num_module; i++)
        {
            string str_i;
            stringstream ss;
            ss << i;
            ss >> str_i;
            pair<float, float> a = FP->F_WidthHeight[str_i];
            pair<float, float> b = FP->F_coordinate[str_i];
            float a1=floor(a.first*1000)/1000, a2=floor(a.second*1000)/1000;
            if(a2/a1 > 2)
                a2 = a2-(a2-2*a1);
            else if(a2/a1 < 0.5)
                a1 = a1-(a1-2*a2);
            ofile << floor(b.first*1000)/1000 << " " << floor(b.second*1000)/1000 << " ";
            ofile << a1 << " " << a2 << endl;
        }

        vector<string>::iterator it;
        for(it=npe.begin(); it!=npe.end(); it++)
        {
            ofile << *it << " ";
        }
    }
    ofile.close();
}