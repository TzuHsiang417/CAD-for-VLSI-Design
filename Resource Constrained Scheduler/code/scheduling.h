#ifndef _NODE_H
#define _NODE_H

#include <vector>
#include <map>
#include <stack>
#include "parameter.h"

using namespace std;

void clean_Node_info();
void get_information(char *);
void output_overcome(char *);
void ALAP_scheduling();
void count_num_descendent();
void list_scheduling_algo();

inline int num_adder, num_multiplier, num_node, num_edge, num_operator;   
struct Node_info   
{
    int node;   
    int predecessor1;   
    int predecessor2;
    int num_descendant; 
    int status; 
    vector<int> successor; 
    char operator_type; 
};

struct Ready_state  //for list scheduling algotithm
{
    int state;
    int node;
    char operator_type;
};

inline struct State_op_num //# of adder and multiplier in each state
{
    int multiplier;
    int adder;
}state_op_num[SIZE];

inline struct In_Out_info  //store input node and output node
{
    vector<int>input;
    vector<int>output;
}i_o_node;

inline map<int, struct Node_info> node_id;
inline map<int, struct Ready_state> ready_state;
inline stack<int> order_of_list;

#endif