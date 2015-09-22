#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "vxcore_lib.h"
#include "vxscripts.h"

int main(int argc, char *argv[]) 
{
    printf("VX database core v 0.01\n");
    /*if(argc!=3) {
                printf("No command-line arguments\n");
                exit(1);
        }
    if((strstr(argv[1], "help")) != NULL){
            printf("read (file name) - read db file\n");
            printf("add (name, type, data) - append variable\n");
            printf("write (file name) - write db file\n");
            printf("print (if (-1) - list all) - print tale or line\n");
    };
    if((strstr(argv[1], "-f")) != NULL){
            printf("Read scrpt file ->%s \n", argv[2]);
            scripts(argv[2]);
    };*/
    //printf ("%s %s\n\n", argv[1], argv[2]);
    v_add("variable_01\n", "root\n", "vchar\n","text 01\n");
    v_add("variable_02\n", "user\n", "vchar\n","text 02\n");
    v_add("variable_03\n", "guest\n", "vchar\n","text 03\n");
    v_add("variable_04\n", "root\n", "vchar\n","text 04\n");
    v_add("variable_05\n", "user\n", "vchar\n","text 05\n");
    
    //v_read("data.db");
    //v_print(1);
    
    v_write("data.db");
    return 0;
};
