#include "scheduling.h"

void list_scheduling_algo()     //list scheduling algorithm
{
    for(int i=0; i<SIZE; i++)
    {
        state_op_num[i].adder = num_adder;
        state_op_num[i].multiplier = num_multiplier; 
    }
    int state = 0;

    while(!order_of_list.empty())
    {
        int compare1 = node_id[order_of_list.top()].predecessor1;
        int compare2 = node_id[order_of_list.top()].predecessor2;
        int time1, time2;
        if (ready_state[compare1].operator_type == ADD)
            time1 = ready_state[compare1].state + 1;
        else if (ready_state[compare1].operator_type == MULTI)
            time1 = ready_state[compare1].state + 3;
        else 
            time1 = 0; 

        if (ready_state[compare2].operator_type == ADD)
            time2 = ready_state[compare2].state + 1;
        else if (ready_state[compare2].operator_type == MULTI)
            time2 = ready_state[compare2].state + 3;
        else
            time2 = 0; 

        if(time1 == 0 && time2 == 0)
            state = 1;
        else if(time1 > time2)
            state = time1;
        else 
            state = time2;
        
        if(node_id[order_of_list.top()].operator_type == ADD)
        {
            while(state_op_num[state].adder <= NOTHING)
                state++;
        }
        else if(node_id[order_of_list.top()].operator_type == MULTI)
        {
            while(state_op_num[state].multiplier<=NOTHING || state_op_num[state+1].multiplier<=NOTHING || state_op_num[state+2].multiplier<=NOTHING)
                state++;
        }

        if(node_id[order_of_list.top()].operator_type == ADD)
            state_op_num[state].adder--;
        else if(node_id[order_of_list.top()].operator_type == MULTI)
        {
            state_op_num[state].multiplier--;
            state_op_num[state+1].multiplier--;
            state_op_num[state+2].multiplier--;
        }
        
        ready_state[order_of_list.top()].node = node_id[order_of_list.top()].node;  
        ready_state[order_of_list.top()].operator_type = node_id[order_of_list.top()].operator_type;
        ready_state[order_of_list.top()].state = state;
        order_of_list.pop(); 
    }
}