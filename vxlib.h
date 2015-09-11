struct TLine
{
   char scene[100];
   char shot[100];
   char data[255];
   char source[255];
   char id[12];
};

void wrile_line(char scene[255], char shot[255], char data[255], char source[255], char id[12])
{
   FILE *fp;
   fp = fopen("data.txt", "a+b");
   fprintf(fp, scene);
   fprintf(fp, shot);
   fprintf(fp, data);
   fprintf(fp, source);
   fprintf(fp, id);
   fclose(fp);
};

void read_line(char *fname)
{
   struct TLine line;
   FILE *fr;

   fr = fopen(fname, "r");
   while (fread (&line, sizeof(struct TLine), 1, fr))
   fclose(fr);
   printf(line.scene, line.shot, line.data, line.source, line.id);   
};

int search_line (char *fname, char *str)
{
        struct TLine line[255];
        FILE *fe;
	
        if((fe = fopen(fname, "r")) == NULL) 
        {
                return(-1);
        }
        fe = fopen("data.txt", "r");
        int i=0;        
        char num[12];
        while(!feof(fe))
        {     
                fgets(line[i].scene, 255, (FILE*)fe);
                fgets(line[i].shot, 255, (FILE*)fe);
                fgets(line[i].data, 255, (FILE*)fe);
                fgets(line[i].source, 255, (FILE*)fe);
                fgets(line[i].id, 255, (FILE*)fe);
                sprintf(num, "%u", i );
                i++;
        }        
        fclose(fe);
        
        i=0;
        int ilend=0;
        while (strlen(line[i].shot) != 0 )
        {
                if((strstr(line[i].shot, str)) != NULL) 
                {
                        printf("A match found on line: %d\n", i);
                        printf(" %s %s %s %s %s",line[i].scene, line[i].shot, line[i].data, line[i].source, line[i].id);
                        ilend++;
                }
                i++;
        }
        //return(0);        
        if( ilend == 0 ) 
        {
                printf("\nSorry, couldn't find a match.\n");
        }
}
