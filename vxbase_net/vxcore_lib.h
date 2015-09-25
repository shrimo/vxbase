#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PROTOPORT         8000          /* default protocol port number */
#define QLEN              6             /* size of request queue        */
#define MAX_SIZE 255

struct VLine
{
   char v_name[MAX_SIZE];
   char v_user[MAX_SIZE];
   char v_type[MAX_SIZE];
   char v_data[MAX_SIZE];
   char v_id[12];
};

struct VLine v_line[1024];

int counter=0;

void v_add(char name[MAX_SIZE], char user[MAX_SIZE], char type[MAX_SIZE],char data[MAX_SIZE]) 
{       
       char num[12];
       
       strcpy(v_line[counter].v_name, name);
       strcpy(v_line[counter].v_user, user);
       strcpy(v_line[counter].v_type, type);
       strcpy(v_line[counter].v_data, data);
       sprintf(num, "%u", counter );
       strcpy(v_line[counter].v_id, strcat (num, "\n"));
       counter++;
};

void v_print(int num) 
{      
    printf("Print data:\n");
        int i=0;
        if (num==-1){
                while (i != counter)
                        {   
                                printf("%s", v_line[i].v_name);
                                printf("%s", v_line[i].v_user);
                                printf("%s", v_line[i].v_type);
                                printf("%s", v_line[i].v_data);
                                printf("%s", v_line[i].v_id);
                                i++;
                        }
        }else{
            printf("%s", v_line[num].v_name);
            printf("%s", v_line[num].v_user);
            printf("%s", v_line[num].v_type);
            printf("%s", v_line[num].v_data);
            printf("%s", v_line[num].v_id);
        }
 }

void v_write(char *fname) 
{       
	FILE *fw;
	fw = fopen(fname, "w+");
	int i=0;
	while (i<counter)
	{   			
		fprintf(fw, v_line[i].v_name);
		fprintf(fw, v_line[i].v_user);
		fprintf(fw, v_line[i].v_type);
		fprintf(fw, v_line[i].v_data);
		fprintf(fw, v_line[i].v_id);
		i++;
	};
	fclose(fw);
};

void v_read (char *fname, char key[255])
{
    //printf("Read %s\n", fname);
    FILE *fe;    
     if((fe = fopen(fname, "rb")) == NULL) 
        {
         printf ("none data\n");
                return(-1);
        }
      fe = fopen(fname, "rb"); /*Read from data file*/
      int i=0;
      while(!feof(fe))
        {     
			fgets(v_line[i].v_name, MAX_SIZE, (FILE*)fe);
			fgets(v_line[i].v_user, MAX_SIZE, (FILE*)fe);
			fgets(v_line[i].v_type, MAX_SIZE, (FILE*)fe);
			fgets(v_line[i].v_data, MAX_SIZE, (FILE*)fe);
			fgets(v_line[i].v_id, MAX_SIZE, (FILE*)fe);
			if (strstr(v_line[i].v_user, key)==NULL)
			{
				i=i;
			}else
			{
				i++;
				counter=i;
			}
        }        
        fclose(fe);    
};

void squeeze (char s[], char s2[]) {
	int k, i, j;
 
	for (k = 0; s2[k] != '\0'; k++) { 
		for (i = j = 0; s[i] != '\0'; i++)
			if (s[i] != s2[k])
				s[j++] = s[i];
		s[j] = '\0';
	}
}
