#include "logicOpt.h"

int  main(int argc, char *argv[])
{
    get_file(argv[1]);
    Quine_McCluskey_ALGO();
    Column_Covering_ALGO();
    create_file(argv[argc-1]);
    return 0;
}