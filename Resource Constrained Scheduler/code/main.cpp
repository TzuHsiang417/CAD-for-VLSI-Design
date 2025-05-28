#include "scheduling.h"

int main(int argc, char *argv[])
{
    get_information(argv[1]);
    count_num_descendent();
    ALAP_scheduling();
    list_scheduling_algo();
    output_overcome(argv[argc-1]);

    return 0;
}