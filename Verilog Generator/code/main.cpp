#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

string bigtosmall(string);

int main(int argc, char *argv[])
{
    ifstream ifile(argv[1], ios::in);   //open file

    if(!ifile)
    {
        cout << "File could not be opened." << endl;
    }

    vector<string> word;    //store the string which is token
	string line;
	const char*cut=" ,#()";
    int line_cnt=0;         
    vector<vector<string> > logic_gate; //store the logic gate info
    
    while (getline(ifile, line))  
    {
        // string轉char *
        char *lineCharArray;

        const int len = line.length();
        lineCharArray = new char[len + 1];
        strcpy(lineCharArray, line.c_str());

        vector<string> tmp_gate;
        char *p;
        p = strtok(lineCharArray, cut); 
        
        while (p)
        {
            if(line_cnt == 3)
                tmp_gate.push_back(p);

            word.push_back(p);
            p = strtok(NULL, cut);
        }
        
        if(line_cnt == 3)
            logic_gate.push_back(tmp_gate);

        if(line.size() == 0)
            line_cnt++;
    }
    ifile.close();
    
    ofstream ofile(argv[argc-1], ios::out); //creat file

    if(ofile.is_open())
    {
        string title = word [0];    //verilog's module title
        vector<int> inputs, outputs, benchmark, wire, tmp_wire;

        vector<string>::iterator it;
        for(it = word.begin(); it != word.end(); it++)
        {
            if(*it == "INPUT")  //inputs
            {
                int tmp_num;
                tmp_num = atoi((*(it+1)).c_str());
                inputs.push_back(tmp_num);
                benchmark.push_back(tmp_num);
            }

            if(*it == "OUTPUT") //outputs
            {
                int tmp_num;
                tmp_num = atoi((*(it+1)).c_str());
                outputs.push_back(tmp_num);
                benchmark.push_back(tmp_num);
            }

            if(*it == "=")  //wire info.
            {
                int tmp_num;
                tmp_num = atoi((*(it-1)).c_str());
                tmp_wire.push_back(tmp_num);
            }

        }
        
        int wrap = 0;
        ofile << "`timescale 1ns/1ps" << endl << endl;
        ofile << "module " << title << " (";
        
        vector<int>::iterator it_benchmark;
        for(it_benchmark = benchmark.begin(); it_benchmark != benchmark.end(); it_benchmark++)  //output benchmark
        {
            ofile << "N" << *it_benchmark ;
            wrap++;
            if(it_benchmark != benchmark.end()-1)
            {
                ofile << ",";
                if(wrap%10 == 0)
                {
                    ofile << endl;
                    for(int i=0; i<9+title.size(); i++)
                        ofile << " ";
                }
            }
            else
                ofile << ");" << endl << endl;
        }

        //create input
        wrap = 0;
        ofile << "input ";
        vector<int>::iterator it_input;
        for(it_input = inputs.begin(); it_input != inputs.end(); it_input++) 
        {
            ofile << "N" << *it_input;
            wrap++;
            if(it_input != inputs.end()-1)
            {
                ofile << ",";
                if(wrap%10 == 0)
                    ofile << endl << "      ";
            }
            else
                ofile << ";" << endl << endl;
        }

        //create output
        wrap = 0;
        ofile << "output ";
        vector<int>::iterator it_output;
        for(it_output = outputs.begin(); it_output != outputs.end(); it_output++)
        {
            ofile << "N" << *it_output;
            wrap++;
            if(it_output != outputs.end()-1)
            {
                ofile << ",";
                if(wrap%10 == 0)
                    ofile << endl << "       ";
            }
            else
                ofile << ";" << endl << endl;
        }
        
        for(int i = 0; i<tmp_wire.size(); i++)  //compare tmp_wire with outputs to save the wire info.
        {
            int save_wire = 0;
            for(int j = 0; j<outputs.size(); j++)
            {
                if(tmp_wire[i] == outputs[j])
                {
                    save_wire = 1;
                }
            }
            if(save_wire == 0)
                wire.push_back(tmp_wire[i]);
        }

        //create wire
        wrap = 0;
        ofile << "wire ";
        vector<int>::iterator it_wire;
        for(it_wire = wire.begin(); it_wire != wire.end(); it_wire++)
        {
            ofile << "N" << *it_wire;
            wrap++;
            if(it_wire != wire.end()-1)
            {
                ofile << ",";
                if(wrap%10 == 0)
                    ofile << endl << "     ";
            }
            else
                ofile << ";" << endl << endl;
        }

        //create logice gate which is stored in double vector
        int num_gate=1;
        for(int i=0; i<logic_gate.size(); i++)
        {
            ofile << bigtosmall(logic_gate[i][2]) << " " << logic_gate[i][2] << logic_gate[i].size()-3 << "_" << num_gate << " ";
            num_gate++;
            ofile << "(N" << logic_gate[i][0];
            for(int j=3; j<logic_gate[i].size(); j++)
                ofile << ", N" << logic_gate[i][j];
            
            ofile << ");" << endl;
        }
        ofile << endl << "endmodule" << endl << endl;
        cout << "File is saved successfully." << endl;
    }
    else
        cout << "File could not be saved." << endl;
    
    ofile.close();

    system("pause");
    return 0;
}

string bigtosmall(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    if(s=="buff")
        return "buf";
    else
        return s;
};