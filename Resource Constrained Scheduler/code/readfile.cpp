#include <fstream>
#include <iostream>
#include "scheduling.h"

void get_information(char *argv)  
{
    ifstream ifile(argv, ios::in); 
    
    if(!ifile) 
        cout << "File can not be opened." << endl;

    ifile >> num_adder;         
    ifile >> num_multiplier;    
    ifile >> num_node;          
    ifile >> num_edge;          
    int tmp_node=0, tmp_pre=0, line_cnt=0;
    char tmp_operator;  
    num_operator = 0;   //# of operator node

    while(ifile >> tmp_node >> tmp_operator)    
    {
        if((tmp_operator == ADD) || (tmp_operator == MULTI))    //if + and *，store node info. into node_id
        {
            node_id[tmp_node].node = tmp_node;
            node_id[tmp_node].operator_type = tmp_operator;
            node_id[tmp_node].status = 0;
            num_operator++;
        }
        if(tmp_operator == 'i') //if input，store into i_o_node
            i_o_node.input.push_back(tmp_node);
        if(tmp_operator == 'o') //if output，store into i_o_node
            i_o_node.output.push_back(tmp_node);
        line_cnt++;
        if(line_cnt == num_node)
            break;
    }

    while(ifile >> tmp_pre >> tmp_node) //store predeccessor
    {
        if(node_id[tmp_node].predecessor1 != 0)
            node_id[tmp_node].predecessor2 = tmp_pre;
        else
            node_id[tmp_node].predecessor1 = tmp_pre;
        node_id[tmp_pre].successor.push_back(tmp_node);
        if(node_id[tmp_node].node == 0 )
            node_id.erase(tmp_node);
        if(node_id[tmp_pre].node == 0 )
            node_id.erase(tmp_pre);
    }
    ifile.close();

    map<int, Node_info>::iterator it_node;
    for(it_node = node_id.begin(); it_node != node_id.end(); it_node++) //find the bottom node except output node in graph and name them BABY
    {
        int check_baby = 0;
        for(int i=0; i<it_node->second.successor.size(); i++)
        {
            for(int j=0; j<i_o_node.output.size(); j++)
            {
                if(it_node->second.successor[i] == i_o_node.output[j])
                {
                    check_baby++;
                    break;
                }
            }
        }
        if(check_baby == it_node->second.successor.size())
            it_node->second.status = BABY;
    }
}

void output_overcome(char *argv)
{
    int latency = 0;
    map<int, Ready_state>::iterator it_t;
    for(it_t = ready_state.begin(); it_t != ready_state.end(); it_t++)  //count latency
    {
        if(it_t->second.operator_type == ADD)
        {
            if(latency < it_t->second.state)
                latency = it_t->second.state;
        }
        else if(it_t->second.operator_type == MULTI)
        {
            if(latency < it_t->second.state+2)
                latency = it_t->second.state+2;
        }
    }
    
    map<int, vector<int> > out;
    for(int state = 1; state<=latency; state++) 
    {
        for(it_t = ready_state.begin(); it_t != ready_state.end(); it_t++)
        {
            if(it_t->second.state == state)
            {
                if(it_t->second.operator_type == MULTI) 
                {
                    out[state].push_back(it_t->second.node);
                    out[state+1].push_back(it_t->second.node);
                    out[state+2].push_back(it_t->second.node);                    
                }
                else
                    out[state].push_back(it_t->second.node); 
            }
        }
    }

    ofstream ofile(argv, ios::out); //output file
    if(ofile.is_open())
    {
        ofile << latency << endl;
        for(int state = 1; state<=latency; state++)
        {
            vector<int>::iterator it_out;
            for(it_out = out[state].begin(); it_out != out[state].end(); it_out++)
            {
                ofile << *it_out;
                if(it_out < out[state].end()-1)
                    ofile << " ";
            }
            if(state < latency)
                ofile << endl;
        }
    }
    else
        cout << "File can not be saved." << endl;

    ofile.close();
}
