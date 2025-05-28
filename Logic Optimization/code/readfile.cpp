#include <iostream>
#include <fstream>
#include "logicOpt.h"

void get_file(char *argv)
{
    ifstream ifile(argv, ios::in);

    if(!ifile)
    {
        cout << "File could not be opened." << endl;
    }

	string line;
	const char*cut=" =+();";
    int line_cnt=1;
    vector<string> func_tmp;
    
    while (getline(ifile, line))  
    {
        char *lineCharArray;
        const int len = line.length();
        lineCharArray = new char[len + 1];
        strcpy(lineCharArray, line.c_str());

        char *p;
        p = strtok(lineCharArray, cut); 

        while (p)
        {
            if(line_cnt == 1)
                input.push_back(p);
            else if(line_cnt == 2)
                output = p;
            else if(line_cnt == 3)
                func_tmp.push_back(p);
            p = strtok(NULL, cut);
        }
        line_cnt++;
    }

    if(input.size()>=2)
        input.erase(input.begin());
    if(func_tmp.size()>=2)
        func_tmp.erase(func_tmp.begin());

    ifile.close();

    vector<string>::iterator it_functmp;
    for(it_functmp = func_tmp.begin(); it_functmp != func_tmp.end(); it_functmp++)
    {
        string term_tmp = *it_functmp;
        string term_binary;

        for(int i=0; i<term_tmp.length(); i++)
        {
            if(term_tmp[i] >= 97 && term_tmp[i] <= 122) //convert a~z into binary 0 or 1 form
            {
                if(i!=0 && term_tmp[i-1]=='!')
                    term_binary += '0';
                else
                    term_binary += '1';
            }
        }
        minterm.push_back(term_binary);
        on_set.push_back(term_binary);
    }
}

void create_file(char *argv)
{
    ofstream ofile(argv, ios::out);
    if(ofile.is_open())
    {
        vector<string> outcome;
        ofile << "INORDER =";
        for(int i=0; i<input.size(); i++)
        {
            ofile << " " << input[i];
        }
        ofile << ";\n";
        ofile << "OUTORDER = " << output << ";\n";
        ofile << output << " = ";
        for(int i=0; i<minimum_cover.size(); i++)
        {
            for(int j=0; j<input.size(); j++)
            {
                if(minimum_cover[i][j] == '-')
                    continue;
                else if(minimum_cover[i][j] == '0')
                {
                    string ss;
                    ss += '!';
                    ss += input[j];
                    outcome.push_back(ss);
                }
                else if(minimum_cover[i][j] == '1')
                {
                    outcome.push_back(input[j]);
                }
            }
            ofile << "(";
            for(int k=0; k<outcome.size(); k++)
            {
                ofile << outcome[k];
                if(k<outcome.size()-1)
                    ofile << "*";
            }
            outcome.clear();
            ofile << ")";
            if(i<minimum_cover.size()-1)
                ofile << "+";
        }
    }
    else
        cout << "The file can not be saved.\n";
    ofile.close();
}
