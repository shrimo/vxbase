#include<stdio.h>
#include <string.h>
#include "table.h"

int main()
{
   struct table Table1;
    
   strcpy( Table1.scene, "Forest\n");
   strcpy( Table1.shot, "shot 01\n"); 
   strcpy( Table1.data, "Retouch wires\n");
   strcpy( Table1.source, "-scene-shot01-data.exr\n");
   strcpy( Table1.id, "001");
   
   FILE *fp;

   fp = fopen("data.txt", "w+");
   fprintf(fp, Table1.scene);
   fprintf(fp, Table1.shot);
   fprintf(fp, Table1.data);
   fprintf(fp, Table1.source);
   fprintf(fp, Table1.id);
   fclose(fp);
   
   printf("write\n");
   
   char buff[255];

   fp = fopen("data.txt", "r");
   int i=1;
   char num[12];
   while(!feof(fp)){ 
     fgets(buff, 255, (FILE*)fp);
     sprintf(num, "%u", i );
     printf(num);
     printf(": %s\n", buff );
     i=i+1;
   };
   
   //fgets(buff, 255, (FILE*)fp);
   //printf("2: %s\n", buff );
   fclose(fp);
   printf("\nread\n");
}
