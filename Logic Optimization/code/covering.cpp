#include "logicOpt.h"

bool can_marked_table(string x, string y)   //Compare prime_implicant with on_set, if on_set is a part of prime_implicant, then mark it as 1 in table
{
    int different_cnt = 0;
    for(int i = 0; i < x.length(); i++)
    {
        if(x[i] == '-')
            continue;
        else if(x[i] != y[i])
            different_cnt++;
    }
    if(different_cnt == 0)
        return 1;
    else
        return 0;
}

void create_table() //create table which is used in covering algo.
{
    table.resize(prime_implicant.size());
    for(int i=0; i<prime_implicant.size(); i++)
        table[i].resize(on_set.size());
    
    for(int i=0; i<prime_implicant.size(); i++)
    {
        for(int j=0; j<on_set.size(); j++)
            table[i][j] = can_marked_table(prime_implicant[i], on_set[j]);
    }
}

void set_covered(int x, int *amount)    //update the column which is covered in 0(x is row)
{
    for(int j=0; j<on_set.size(); j++)
    {
        if(table[x][j] == 1)
        {
            *amount = *amount - 1;
            for(int i=0; i<prime_implicant.size(); i++)
                table[i][j] = 0;
        }
    }
}

void column_has_single_1(int *amount)
{
    for(int j=0; j<on_set.size(); j++)
    {
        int mark_cnt = 0;   
        int mark_position;  
        for(int i=0; i<prime_implicant.size(); i++)
        {
            if(table[i][j] == 1)
            {    
                mark_cnt++;
                mark_position = i;
            }
        }
        if(mark_cnt == 1)   
        {
            minimum_cover.push_back(prime_implicant[mark_position]);    
            set_covered(mark_position, amount); 
        }
    }
}

void minimum_set_of_row(int *amount) 
{
    while(*amount != 0) 
    {
        int max_row;    
        int num = 0;    
        for(int i=0; i<prime_implicant.size(); i++)
        {   
            int num_tmp = 0;
            for(int j=0; j<on_set.size(); j++)
            {
                if(table[i][j] == 1)
                {
                    num_tmp++;
                }
            }
            if(num < num_tmp)
            {
                num = num_tmp;
                max_row = i;
            }
        }
        minimum_cover.push_back(prime_implicant[max_row]);  
        set_covered(max_row, amount);   
    }
}

void Column_Covering_ALGO() //Column Covering
{
    int on_set_amount = on_set.size();
    create_table();
    column_has_single_1(&on_set_amount);
    minimum_set_of_row(&on_set_amount);

    FreeVector(on_set);
    FreeVector(prime_implicant);
    FreeVector(table);
}
