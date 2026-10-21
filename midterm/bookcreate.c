#include <stdio.h> 
#include "student.h"
int main(int argc, char* argv[])  
{ 
   struct student rec;
   FILE *fp;

   if (argc != 2) {
      fprintf(stderr,"How to use: %s ",argv[0]);
      exit(1); 
   }

   fp = fopen(argv[1], "wb");
   printf("%-9s %-7s %-4s %-2s %-1s %-0s\n","ID","bookName","author","year","numofborrw","borrw"); 
   while (scanf("%d %s %d", &rec.id, rec.name, &rec.score) == 3) 
      fwrite(&rec, sizeof(rec), 1, fp);

   fclose(fp);
   exit(0);
} 
struct student {
   int ID; 
   char bookName[20]; 
   short author;
   int year;
   int numofborrw;
   char borrw[10];
};


