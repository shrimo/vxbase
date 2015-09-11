struct TLine
{
   char  scene[100];
   char shot[100];
   char  data[255];
   char  source[255];
   char   id[12];
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

void read_line()
{
   struct TLine line;
   FILE *fr;

   fr = fopen("data.txt", "r");
   while (fread (&line, sizeof(struct TLine), 1, fr))
   fclose(fr);
   printf(line.scene, line.shot, line.data, line.source, line.id);   
};
