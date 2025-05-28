#include "floorplan.h"

void FloorPlanning::M1(vector<string>&npe)  //M1: swap any two adjacent operand
{
    vector<int>operand_position;

    for(int i=0; i<npe.size(); i++)         
    {
        if(npe[i]!="H" && npe[i]!="V")
            operand_position.push_back(i);
    }
    int num = operand_position.size();
    int x = rand()%(num-1);                 
    vector<string>::iterator it1, it2;
    it1 = npe.begin()+operand_position[x];  
    it2 = npe.begin()+operand_position[x+1];
    iter_swap(it1, it2);                    
    FreeVector(operand_position);
}

void FloorPlanning::M2(vector<string>&npe)  //M2: complement operator chain
{
    vector<int> chain_top;

    for(int i=1; i<npe.size(); i++)         //record location of top of operator chain
    {
        if((npe[i-1]!="H" && npe[i-1]!="V") && (npe[i]=="H" || npe[i]=="V"))
            chain_top.push_back(i);
    }
    int num = chain_top.size();
    int x = rand()%num;                
    int i = chain_top[x];

    while(npe[i]=="H" || npe[i]=="V")       
    {
        if(npe[i] == "H")
            npe[i] = "V";
        else if(npe[i] == "V")
            npe[i] = "H";
        i++;
        if(i >= npe.size())
            break;
    }
    FreeVector(chain_top);
}

void FloorPlanning::M3(vector<string>&npe)  //M3: swap any two adjacent operand & operator
{
    vector<int> adj_position;
    vector<string> npe_temp = npe;

    for(int i=0; i<npe_temp.size()-1; i++)  
    {
        if((npe_temp[i]!="H" && npe_temp[i]!="V") && (npe_temp[i+1]=="H" || npe_temp[i+1]=="V"))
            adj_position.push_back(i);
    }

    int num_try = 0;                        
    do{
        int num = adj_position.size();
        int x = rand()%(num-1);             
        int i = adj_position[x];
        vector<string>::iterator it1, it2;
        it1 = npe_temp.begin()+i-1;
        it2 = npe_temp.begin()+i;
        iter_swap(it1, it2);                
        if(Check_ballot(npe_temp) && Check_consecutive(npe_temp))   //check if the NPE satisfies the rule of ballor and consecutive
            break;                          
        else                                
        {
            npe_temp = npe;
            num_try++;                     
        }
    }while(num_try < M3_TRY);               
    npe = npe_temp;
    FreeVector(adj_position);
    FreeVector(npe_temp);
}

bool FloorPlanning::Check_consecutive(vector<string>&npe)       //check if there is consecutive
{
    vector<string>::iterator it_name;
    for(it_name = npe.begin(); it_name != npe.end(); it_name++)
    {
        if(*it_name=="H" || *it_name=="V")                      //operator or not
        {   
            if(*it_name == *(it_name-1))                        //if operator is same as the next operator,  return false
                return 0;
        }
    }
    return 1;
}

bool FloorPlanning::Check_ballot(vector<string>&npe)            //check ballot
{
    vector<string>::iterator it_name;
    int num_operand = 0;
    int num_operator =0;
    for(it_name = npe.begin(); it_name != npe.end(); it_name++)
    {
        if(*it_name == "V" || *it_name == "H")      //if operator
            num_operator++;
        else if(*it_name != "V" && *it_name != "H") //if operand
            num_operand++;
        
        if(num_operator >= num_operand)             //if # operator is larger than # operand, return false
            return 0;
    }
    return 1;
}