#include "floorplan.h"
#include "readfile.h"

int main(int argc, char *argv[])
{
    cout.setf(ios::fixed);      
    cout.precision(3);          
    map<string, float> module;
    int num_module;
    clock_t t1, t2;
    t1 = clock();

    if(!ReadFile(argv[1], &num_module, module))
    {
        cout << "File can not be OPENED!!!" << endl;
        return 0;
    }

    FloorPlanning *FP = new FloorPlanning(module);
    vector<string> npe;
    
    FP->InitialNPE(npe);

    cout << "\nInitial NPE is ";
    FP->printNPE(npe);
    cout << "\nInitial cost is " << FP->Cost(npe) << endl;

    srand(SEED);
    FP->Wong_Liu_ALGO(npe);

    cout << "\nOptimized NPE is ";
    FP->printNPE(npe);
    cout << "\nOptimized cost is " << FP->Cost(npe) << endl;

    t2 = clock();
    cout << "\nSpend " << (t2-t1)/((double)(CLOCKS_PER_SEC)) << " s" << endl;
    FP->Create_Information(npe);

    Create_file(argv[argc-1], num_module, FP, npe);

    return 0;
}