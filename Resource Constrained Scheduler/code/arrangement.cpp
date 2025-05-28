#include "scheduling.h"

void count_num_descendent() //# descendent of each node
{
    for(int i=0; i<num_operator; i++)
    {
        map<int, Node_info>::iterator it_node;
        for(it_node = node_id.begin(); it_node != node_id.end(); it_node++)
        {
            for(int j=0; j<it_node->second.successor.size(); j++)
            {
                if(it_node->second.status == BABY)  //if BABY, # descendent would be 0
                {
                    it_node->second.num_descendant = 0;
                    break;
                }else if(node_id[it_node->second.successor[j]].node == 0)   //if output node, continue
                    continue;
                else if(it_node->second.num_descendant <= node_id[it_node->second.successor[j]].num_descendant) //if # descendent of current node is less than # descendent of successor, # descendent of current node would be # descendent of successor +1
                    it_node->second.num_descendant = node_id[it_node->second.successor[j]].num_descendant+1;
            }
        }
    }
    clean_Node_info();
}

void clean_Node_info()  //delete the key element which is wrong in map
{
    int amount=0;
    map<int, Node_info>::iterator it_t;
    for(it_t = node_id.begin(); it_t != node_id.end(); it_t++)
    {
        amount++;
    }

    for(int i=0; i<amount-num_operator; i++)
    {
        map<int, Node_info>::iterator it_t1;
        for(it_t1 = node_id.begin(); it_t1 != node_id.end(); it_t1++)
        {
            if(it_t1->second.node == 0)
            {
                node_id.erase(it_t1->first);
                break;
            }
        }
    }
}

void ALAP_scheduling()  //ALAP scheduling
{
    for(int i=0; i<num_operator; i++)
    {
        map<int, Node_info>::iterator it_t;
        for(it_t = node_id.begin(); it_t != node_id.end(); it_t++)
        {
            if(it_t->second.num_descendant == i)
            {
                order_of_list.push(it_t->second.node);
            }
        }
    }
}