struct VLine
{
   char v_name[100];
   char v_type[255];
   char v_data[255];
   char v_id[12];
};

struct VLine v_line[1024];

int counter=0;

void v_add(char name[255], char type[100],char data[255]) 
{       
       char num[12];
       
       strcpy(v_line[counter].v_name, name);
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
                                printf("%s", v_line[i].v_type);
                                printf("%s", v_line[i].v_data);
                                printf("%s", v_line[i].v_id);
                                i++;
                        }
        }else{
            printf("%s", v_line[num].v_name);
            printf("%s", v_line[num].v_type);
            printf("%s", v_line[num].v_data);
            printf("%s", v_line[num].v_id);
        }
 }

void v_write(char fname) 
{       
        FILE *fw;
        fw = fopen(fname, "wb");
        int i=0;
        while (i<counter)
        {   
                fprintf(fw, v_line[i].v_name);
                fprintf(fw, v_line[i].v_type);
                fprintf(fw, v_line[i].v_data);              
                fprintf(fw, v_line[i].v_id);
                i++;
         };
        fclose(fw);
};

int v_read (char *fname)
{
    printf("Read %s\n", fname);
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
                fgets(v_line[i].v_name, 255, (FILE*)fe);
                fgets(v_line[i].v_type, 255, (FILE*)fe);
                fgets(v_line[i].v_data, 255, (FILE*)fe);
                fgets(v_line[i].v_id, 255, (FILE*)fe);
                i++;
                counter=i;
        }        
        fclose(fe);    
}

void squeeze (char s[], char s2[]) {
	int k, i, j;
 
	for (k = 0; s2[k] != '\0'; k++) { 
		for (i = j = 0; s[i] != '\0'; i++)
			if (s[i] != s2[k])
				s[j++] = s[i];
		s[j] = '\0';
	}
}
