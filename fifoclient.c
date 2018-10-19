#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *katalog, tekst[80], pozycja_pliku[80], end[] = "end";
	DIR *dir;
	struct dirent *pozycja; 
	FILE *fp;
	
	switch(argc)
	{
         case 1: katalog = ".";
                 break;
         case 2: katalog = argv[1];
                 break;
         default : printf("Poprawna skladnia:\t%s katalog\n", argv[0]);
                   exit(1);
        }
	
	if ((dir = opendir(katalog)) == NULL)
	{
		perror("Blad opendir");
		return 1;
	}
	
	errno = 0;
	while ((pozycja = readdir(dir)) != NULL) {
		strcpy(pozycja_pliku, argv[1]);
		strcat(pozycja_pliku, "/");
		strcat(pozycja_pliku, pozycja->d_name);
		if (pozycja->d_type == DT_FIFO) {
			while (1) {
			if((fp = fopen(pozycja_pliku, "w")) == NULL) { 
    				perror("fopen"); 
    				exit(1); 
  			}
			scanf("%s", tekst);
			if(strcmp(tekst, end) == 0) {
				break;}
  			if (fputs(tekst, fp)==EOF) { 
    				perror("fputs"); 
    				exit(1); 
   			} }
		}
	}
	if (errno)
	{
		perror("Blad readdir");
		return 1;
	}
	if (closedir(dir) == -1)
	{
		perror("Blad closedir");
		return 1;
	}
	fclose(fp); 
	return 0;
}
     
