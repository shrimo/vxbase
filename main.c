#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vxlib.h"

int main(int argc, char *argv[])
{
    struct TLine _line;
    //wrile_line("Forest\n", "shot_01\n", "Retouch wires\n",  "-scene-shot01-data.exr\n", "001\n");
    //wrile_line("City\n", "shot_02\n", "Retouch wires\n",  "-scene-shot02-data.exr\n", "002\n");
    //wrile_line("River\n", "shot_03\n", "Retouch wires\n",  "-scene-shot03-data.exr\n", "003\n");
    
    //printf("->Load data\n\n");
    //read_line("data.txt");
    
    printf("\n->Search line\n");
    search_line("data.txt",argv[1]);
    
    printf("\n->End\n");
    return 0;
};
