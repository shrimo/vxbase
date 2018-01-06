#define MAX_SIZE 255

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include "vxcore_lib.h"

struct User_Base
{
	char user[MAX_SIZE];
	char pass[MAX_SIZE];
};

struct User_Base user_base[1024];
int u_count=0;

void add_user(char user[MAX_SIZE], char pass[MAX_SIZE]) 
{              
       strcpy(user_base[u_count].user, user);
       strcpy(user_base[u_count].pass, pass);
       u_count++;
};

void write_user(char fname[MAX_SIZE])
{       
        FILE *fw;
        fw = fopen(fname, "wb");
        int i=0;
        while (i<u_count)
        {   
			fprintf(fw, user_base[i].user);
			fprintf(fw, user_base[i].pass);                
			i++;
         };
        fclose(fw);
};

int get_user (char ffname[MAX_SIZE])
{			
	printf("read from file: %s\n", ffname);
    FILE *fe;
    
    if((fe = fopen(ffname, "rb")) == NULL)
	{
		printf ("none data\n");
		return(0);
	}
	fe = fopen(ffname, "rb"); //Read from data file
	int i=0;	
	while(!feof(fe))
	{     
		fgets(user_base[i].user, MAX_SIZE, (FILE*)fe);
		fgets(user_base[i].pass, MAX_SIZE, (FILE*)fe);
		i++;
		u_count=i;
	}        
	fclose(fe);
	return(0);
};

char * select_user (char s_user[MAX_SIZE])
{
	int i=0;	
	char *s_u = (char *) malloc(sizeof(char) * 5);
	strcpy(s_u, "False");
	
	while (strlen(user_base[i].user) != 0 ) /*If variable is not empty*/
	{
		if((strstr(user_base[i].user, s_user)) != NULL) /*Search by keyword*/
		{
			strcpy(s_u, "True");
			//printf("%s\n",s_u);		
		}
		i++;
	}	
	return s_u;
	free (s_u);
}

int main(int argc, char *argv[])
{		
	//add_user("root\n","qwe\n");
	//add_user("guest\n","ewq\n");
	//add_user("user\n","asd\n");
	//write_user("user.vx");
	get_user("user.conf");	
	char *nnn=select_user("guest");
	printf("%s\n", nnn);
	return(0);
};
