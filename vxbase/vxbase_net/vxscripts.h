/*read scrpipts file and interpretation*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct S_Line
{
    char in_line[255];
};

char fdir[255];

void scripts (char *fname, char user[255]){
	
    struct S_Line s_line[255];
    char tmp[255];
	int i=0;
    char buff[255];
    
    FILE *fs;
    if((fs = fopen(fname, "rb")) == NULL) 
        {
         printf ("none data\n");
                return(-1);
        }
      fs = fopen(fname, "rb"); /*Read from data file*/
    while(!feof(fs))
        {     
                fgets(buff, 255, (FILE*)fs);
                strcpy(s_line[i].in_line, buff);
                i++;
        }        
     fclose(fs);    

     i=0;
     int dir;
     int istr;
     
     while(strstr(s_line[i].in_line, "end") == NULL)
     {		
        if(strstr(s_line[i].in_line, "read") != NULL) 
        {            
            printf("->find read\n");
            if(strstr(s_line[i].in_line, "(\"") != NULL) 
            {
                printf("-->find (\"\n");     
                istr = strcspn (s_line[i].in_line, "(\"\")");
                dir=istr+1;                
                strcpy(tmp, s_line[i].in_line);
                squeeze(tmp,"\")\n");                                                
                v_read(&tmp[dir],user);
            }           
        }
        if(strstr(s_line[i].in_line, "print") != NULL) 
        {            
            printf("->find print\n");
            if(strstr(s_line[i].in_line, "(\"") != NULL) 
            {
                printf("-->find (\"\n");                
                istr = strcspn (s_line[i].in_line, "(\"\")");
                dir=istr+1;                
                strcpy(tmp, s_line[i].in_line);
                squeeze(tmp,"\")\n");                                
                v_print(atoi(&tmp[dir]));
            }           
        }
        i++;
     }
 }
