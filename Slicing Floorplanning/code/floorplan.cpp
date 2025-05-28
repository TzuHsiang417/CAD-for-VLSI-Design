#include "floorplan.h"

void FloorPlanning::InitialNPE(vector<string>&npe)  //create initial NPE
{
    map<string, float>::iterator it_m;
    it_m = module.begin();
    npe.push_back(it_m->first);
    it_m++;

    npe.push_back(it_m->first);
    it_m++;
    int i=0;
    if((module.size()-1)/2 >= 50)                   //according to # module, creating different initial NPE
    {
        for(; it_m!=module.end(); it_m++)           //V V V V V V V
        {
            npe.push_back("V");
            npe.push_back(it_m->first);
        }
    }
    else
    {
        for(; it_m!=module.end(); it_m++)           //V H V H V H V
        {
            if(i%2 == 0)
                npe.push_back("V");
            else
                npe.push_back("H");
            npe.push_back(it_m->first);
            i++;
        }
    }
    npe.push_back("V");
}









void FloorPlanning::Create_Information(vector<string>&npe)      //find the width length and coordinate of each module in optimized NPE
{
    vector<block*>NPE_block = createNPE_Block(npe);

    vector<block*>::iterator it_block;
    stack<block*>block_stack1;      
    stack<block*>block_stack2;
    float cost = 9999999.0;

    for(it_block = NPE_block.begin(); it_block != NPE_block.end(); it_block++)  
    {
        block *opn = *it_block;
        if((opn->name!="H") && (opn->name!="V"))
            block_stack1.push(opn);
        else
        {
            block *b1 = block_stack1.top();
            block_stack1.pop();
            block_stack2.push(b1);
            block *b2 = block_stack1.top();
            block_stack1.pop();
            block_stack2.push(b2);
            Combination(b1, b2, opn);
            block_stack1.push(opn);
        }
    }
    
    map<block*, pair<float, float> > WH_temp;           
    map<block*, pair<float, float> > coordinate_temp;   
    block *total = block_stack1.top();                  
    vector<pair<float, float> >::iterator it_WH;
    for(it_WH = (total->WidthHeight).begin(); it_WH != (total->WidthHeight).end(); it_WH++) 
    {
        float total_area = (*it_WH).first * (*it_WH).second;
        if(cost > total_area)
        {
            cost = total_area;
            WH_temp[total] = make_pair((*it_WH).first, (*it_WH).second);
            coordinate_temp[total] = make_pair(0.0, 0.0);
        }
    }

    while(!block_stack1.empty())        
    {
        block *b1 = block_stack1.top();         
        block_stack1.pop();                     
        float b1_w = WH_temp[b1].first;         
        float b1_h = WH_temp[b1].second;        
        float b1_x = coordinate_temp[b1].first; 
        float b1_y = coordinate_temp[b1].second;

        if(b1->name == "H" || b1->name == "V")  
        {
            block *b2 = block_stack2.top();     
            block_stack2.pop();
            block_stack1.push(b2);              
            block *b3 = block_stack2.top();
            block_stack2.pop();
            block_stack1.push(b3);

            vector<pair<float, float> >::iterator it_b2;
            vector<pair<float, float> >::iterator it_b3;
            for(it_b2 = (b2->WidthHeight).begin(); it_b2 != (b2->WidthHeight).end(); it_b2++)   
            {
                float b2_w = (*it_b2).first;
                float b2_h = (*it_b2).second;
                float b2_x;
                float b2_y;
                bool complete = 0;

                for(it_b3 = (b3->WidthHeight).begin(); it_b3 != (b3->WidthHeight).end(); it_b3++)
                {
                    float b3_w = (*it_b3).first;
                    float b3_h = (*it_b3).second;
                    float b3_x;
                    float b3_y;
                    float height = 0.0;
                    float width = 0.0;

                    if(b1->name == "H")         
                    {
                        height = b2_h + b3_h;
                        width = max(b2_w, b3_w);    
                        b2_x = b1_x;            
                        b2_y = b1_y;            
                        b3_x = b1_x;            
                        b3_y = b1_y + b2_h;     
                    }
                    else if(b1->name == "V")
                    {
                        width = b2_w + b3_w;    
                        height = max(b2_h, b3_h);
                        b2_x = b1_x;            
                        b2_y = b1_y;            
                        b3_x = b1_x + b2_w;     
                        b3_y = b1_y;            
                    }
                    if(height == b1_h && width == b1_w)     
                    {
                        WH_temp[b2] = make_pair(b2_w, b2_h);    
                        WH_temp[b3] = make_pair(b3_w, b3_h);
                        coordinate_temp[b2] = make_pair(b2_x, b2_y);
                        coordinate_temp[b3] = make_pair(b3_x, b3_y);
                        complete = 1;
                        break;
                    }
                }
                if(complete)
                    break;
            }
        }
        else if(b1->name != "H" && b1->name != "V")     
        {
            F_WidthHeight[b1->name] = make_pair(b1_w, b1_h);
            F_coordinate[b1->name] = make_pair(b1_x, b1_y);
        }
    }

    vector<block*>::iterator it_free;                   
    for(it_free = NPE_block.begin(); it_free!=NPE_block.end(); it_free++)
    {
        delete *it_free;
        *it_free = NULL;
    }

    FreeVector(NPE_block);
}

void FloorPlanning::printNPE(vector<string>&npe)        //print NPE
{
    vector<string>::iterator it;
    for(it=npe.begin(); it!=npe.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}