#include "logicOpt.h"
#include <algorithm>

bool compare_num_of_1(string x, string y)   //compare the # of 1
{
    int a = 0, b = 0;
    for(int i=0; i<x.length(); i++)
    {
        a = a+x[i]-'0';
        b = b+y[i]-'0';
    }
    return a < b;
}

void sort_minterm() //according # of 1，arrange in ascending power
{
    sort(minterm.begin(), minterm.end(), compare_num_of_1);
    sort(on_set.begin(), on_set.end(), compare_num_of_1);
}

bool can_merge(string x, string y)  //check two strings if can be merged
{
    int different_cnt = 0;
    for(int i = 0; i < x.length(); i++)
    {
        if(x[i] != y[i])
            different_cnt++;
    }
    if(different_cnt == 1)  //if there is a different char, merge them
        return 1;
    else
        return 0;
}

string merge(string x, string y)    //merge two strings
{
    string merge_implicant;
    for(int i=0; i<x.length(); i++)
    {
        if(x[i] == y[i])
            merge_implicant += x[i];
        else if(x[i] != y[i])   //set different char as '-'
            merge_implicant += '-';
    }
    return merge_implicant;
}

void Quine_McCluskey_ALGO() //Quine McCluskey
{
    sort_minterm(); //ascending power

    while(!minterm.empty())
    {
        bool merged_mark[minterm.size()];   //merged or not
        for(int i=0; i<minterm.size(); i++) 
            merged_mark[i] = 0;
        vector<string> implicant_tmp;

        for(int i=0; i<minterm.size(); i++)
        {
            for(int j=i+1; j<minterm.size(); j++)
            {
                if(can_merge(minterm[i], minterm[j]) == MERGED)
                {
                    implicant_tmp.push_back(merge(minterm[i], minterm[j]));
                    merged_mark[i] = MERGED;
                    merged_mark[j] = MERGED;
                }
            }

            if(merged_mark[i] == NO_MERGED)
            {
                prime_implicant.push_back(minterm[i]);
            }
        }

        if(!implicant_tmp.empty())
        {
            vector<string>::iterator it,it1;
            for(it=++implicant_tmp.begin(); it!=implicant_tmp.end();)
            {
                it1 = find(implicant_tmp.begin(), it, *it);
                if (it1 != it)
                    it = implicant_tmp.erase(it);
                else
                    it++;
            }
        }

        minterm.clear();

        for(int i=0; i<implicant_tmp.size(); i++)
            minterm.push_back(implicant_tmp[i]);
    }
    FreeVector(minterm);
}