#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vxlib.h"

int main(void)
{
    struct TLine _line;
    //wrile_line("Forest\n", "shot 01\n", "Retouch wires\n",  "-scene-shot01-data.exr\n", "001\n");
    //wrile_line("City\n", "shot 02\n", "Retouch wires\n",  "-scene-shot02-data.exr\n", "002\n");
    //wrile_line("River\n", "shot 03\n", "Retouch wires\n",  "-scene-shot03-data.exr\n", "003\n");
    printf("->Load data\n\n");
    read_line();
    printf("\n->End\n");
    return 0;
};
