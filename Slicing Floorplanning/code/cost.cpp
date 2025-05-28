#include "floorplan.h"

vector<block*> FloorPlanning::createNPE_Block(vector<string>&npe)   //creat the block for each element in NPE
{
    vector<block*> NPE_Block;

    vector<string>::iterator it;
    for(it=npe.begin(); it!=npe.end(); it++)
    {
        if(*it!="H" && *it!="V")    //if the element is operand，give all possible width and length to its block
        {
            vector<pair<float, float> >width_height;
            float area = module[*it];
            float w1, h1;
            pair<float, float>set;

            w1 = sqrt(area*MIN_ASPECT);
            h1 = sqrt(area/MIN_ASPECT);
            set = make_pair(w1, h1);
            width_height.push_back(set);

            w1 = sqrt(area*SMALLER_ASPECT1);
            h1 = sqrt(area/SMALLER_ASPECT1);
            set = make_pair(w1, h1);
            width_height.push_back(set);

            w1 = sqrt(area*SMALLER_ASPECT2);
            h1 = sqrt(area/SMALLER_ASPECT2);
            set = make_pair(w1, h1);
            width_height.push_back(set);

            w1 = sqrt(area*SMALLER_ASPECT3);
            h1 = sqrt(area/SMALLER_ASPECT3);
            set = make_pair(w1, h1);
            width_height.push_back(set);

            w1 = sqrt(area);
            h1 = sqrt(area);
            set = make_pair(w1, h1);
            width_height.push_back(set);

            w1 = sqrt(area*LARGER_ASPECT1);
            h1 = sqrt(area/LARGER_ASPECT1);
            set = make_pair(w1, h1);
            width_height.push_back(set);

            w1 = sqrt(area*LARGER_ASPECT2);
            h1 = sqrt(area/LARGER_ASPECT2);
            set = make_pair(w1, h1);
            width_height.push_back(set);

            w1 = sqrt(area*LARGER_ASPECT3);
            h1 = sqrt(area/LARGER_ASPECT3);
            set = make_pair(w1, h1);
            width_height.push_back(set);

            w1 = sqrt(area*MAX_ASPECT);
            h1 = sqrt(area/MAX_ASPECT);
            set = make_pair(w1, h1);
            width_height.push_back(set);

            block *macro = new block(*it, width_height);
            NPE_Block.push_back(macro);
            FreeVector(width_height);
        }
        else    //if the element is operator, we do not set the width and length, but creat empty block
        {
            vector<pair<float, float> >width_height;    //空的
            block *macro = new block(*it, width_height);
            NPE_Block.push_back(macro);
            FreeVector(width_height);
        }
    }
    return NPE_Block;
}

void FloorPlanning::Combination(block*operand1, block*operand2, block*operator1)    //begin the combination of NPE
{
    vector<pair<float, float> >::iterator it_opn1;  //operand1
    for(it_opn1=(operand1->WidthHeight).begin(); it_opn1!=(operand1->WidthHeight).end(); it_opn1++)
    {
        float w1 = (*it_opn1).first;        //operand1's width
        float h1 = (*it_opn1).second;       //operand1's height
        vector<pair<float, float> >::iterator it_opn2;  //operand2
        for(it_opn2=(operand2->WidthHeight).begin(); it_opn2!=(operand2->WidthHeight).end(); it_opn2++)
        {
            float width = 0.0;
            float height = 0.0;
            float w2 = (*it_opn2).first;    //operand2's width
            float h2 = (*it_opn2).second;   //operand2's height

            if(operator1->name == "H")      //if operator is H
            {
                height = h1+h2;             //sum height
                width = max(w1,w2);         //pick up width's maximum
            }
            else if(operator1->name == "V") //if operator is V
            {
                width = w1+w2;              //sum width
                height = max(h1,h2);        //pick up height's maximum
            }
            pair<float, float> WH_temp;
            WH_temp = make_pair(width, height);
            (operator1->WidthHeight).push_back(WH_temp); 
        }
    }

    //delete the assembly of width & length which isn't optimized in operator' block
    vector<pair<float, float> >::iterator it_WHcurrent;
    for(it_WHcurrent = (operator1->WidthHeight).begin(); it_WHcurrent != (operator1->WidthHeight).end(); it_WHcurrent++)
    {
        float w_current = (*it_WHcurrent).first;
        float h_current = (*it_WHcurrent).second;

        vector<pair<float, float> >::iterator it_WHnext;
        for(it_WHnext = it_WHcurrent+1; it_WHnext != (operator1->WidthHeight).end(); /*it_WHnext++*/)
        {
            float w_next = (*it_WHnext).first;
            float h_next = (*it_WHnext).second;
            if((w_current >= w_next) && (h_current >= h_next))
            {
                it_WHcurrent = (operator1->WidthHeight).erase(it_WHcurrent);
                it_WHcurrent--;
                break;
            }
            if((w_next >= w_current) && (h_next >= h_current))
            {
                it_WHnext = (operator1->WidthHeight).erase(it_WHnext);
            }
            else
                it_WHnext++;
        }
    }
}

float FloorPlanning::Cost(vector<string>&npe)       //cost
{
    vector<block*>NPE_block = createNPE_Block(npe); 
    vector<block*>::iterator it_block;
    stack<block*>block_stack;                       
    float cost = 9999999.0;

    for(it_block = NPE_block.begin(); it_block != NPE_block.end(); it_block++)  //Combination
    {
        block *opn = *it_block;
        if((opn->name!="H") && (opn->name!="V"))    
            block_stack.push(opn);
        else                                        
        {
            block *b1 = block_stack.top();          
            block_stack.pop();                      
            block *b2 = block_stack.top();          
            block_stack.pop();                      
            Combination(b1, b2, opn);               
            block_stack.push(opn);                  
        }
    }

    block *total = block_stack.top();               
    vector<pair<float, float> >::iterator it_WH;
    for(it_WH = (total->WidthHeight).begin(); it_WH != (total->WidthHeight).end(); it_WH++) //take out minimum cost
    {
        float total_area = (*it_WH).first * (*it_WH).second;    //area=width*height
        if(cost > total_area)
            cost = total_area;
    }

    vector<block*>::iterator it_free;
    for(it_free = NPE_block.begin(); it_free!=NPE_block.end(); it_free++)
    {
        delete *it_free;
        *it_free = NULL;
    }

    FreeVector(NPE_block);
    return cost;
}