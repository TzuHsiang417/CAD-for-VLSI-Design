#include "floorplan.h"

void FloorPlanning::Wong_Liu_ALGO(vector<string>&npe)   //Wong Liu Algorithm
{
    vector<string> best = npe;     
    vector<string> new_npe = npe;   
    float T0 = 3000.00;             //initial temprature
    int M = 0;                      //M：M1、M2、M3
    int MT = 0;                     //times of move
    int uphill = 0;                 //uphill
    int reject = 0;                 //reject
    int N = K*npe.size();           //N=K*n
    float T = T0;                   
    float best_cost = Cost(best);   
    float old_cost = Cost(npe);     
    time_t t1, t2;
    t1 = time(NULL);

    do{
        reject = 0;             //initialize
        MT = 0;
        uphill = 0;

        do{
            M = rand()%3 + 1;   //do M1, M2 or M3 randomly

            switch(M)
            {
            case 1:
                M1(new_npe);
                break;
            case 2:
                M2(new_npe);
                break;
            case 3:
                M3(new_npe);
                break;
            }

            MT++;               //move time++
            float new_cost = Cost(new_npe);             
            float delta_cost = new_cost - old_cost;     //variation of cost
            double probability = (double)rand()/RAND_MAX;           
            if(delta_cost<=0 || probability<exp(-1*delta_cost/T))   
            {
                if(delta_cost > 0)         
                    uphill++;
                npe = new_npe;              
                old_cost = Cost(npe);   
                if(new_cost < best_cost)    
                {
                    best = new_npe;         
                    best_cost = Cost(best); 
                }
            }
            else
                reject++;

            new_npe = npe;
            t2 = time(NULL);

            if((t2-t1)>=TIME_LIMIT)         
                break;
        } while(uphill<=N && MT<=2*N);
        
        if(T>30)        
            T = RATIO*T;
        else
            T = FROZEN_RATIO*T;

        t2 = time(NULL);
    } while((reject/MT)<=0.95 && T>=EPSILON && (t2-t1)<TIME_LIMIT);
    npe = best;
}