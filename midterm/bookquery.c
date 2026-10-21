#include <stdio.h> 
#include "student.h"
int main(int argc, char* argv[]) 
{ 
   struct student rec;
   FILE *fp;
   if (argc != 2) { 
      fprintf(stderr, "How to use: %s FileName\n", argv[0]);
      return 1; 
   }
   if ((fp = fopen(argv[1], "rb")) == NULL ) {
      fprintf(stderr, "Error Open File\n");
      return 2;
   }
   printf("--bookquery--\n");
   printf("0: list of all books, 1: list of available books");
   prinf("%d\n",num1);
   printf("%10s %6s %6s %10s %10s %10s\n", "ID","bookName", "author","year","numofborrow","borrw");
   
   
   while (fread(&rec, sizeof(rec), 1, fp) > 0) 
      if (rec.id != 0)
         printf("%10d %6s %6d %10s %10s %10s\n", rec.id,  rec.bookName,  rec.author, rec.year, rec.numofborrow, rec.borrw);
   
   fclose(fp);
   return 0;
} 


