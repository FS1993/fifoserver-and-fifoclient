#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	char *katalog, readbuf[80], pozycja_pliku[80], fifo[10];
	DIR *dir;
	struct dirent *pozycja;
	int licznik = 0; 
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
		licznik++;
		printf("%s\n", pozycja_pliku);
		
			if ((fp=fopen(pozycja_pliku, "r"))==NULL) {
     				perror("fopen");
				exit(1);
			}
    			if (fgets(readbuf, 80, fp)==NULL) {
      				perror("fgets"); 
      				exit(1); } 
			printf("Otrzymany tekst: %s\n", readbuf);}
	}
	if (licznik == 0) {
		printf("Prosze podac nazwe pliku FIFO: ");
		scanf("%s", fifo);
		umask(0);
		mknod(fifo, S_IFIFO|0666, 0);
		if ((fp=fopen(fifo, "r"))==NULL) {
			perror("fopen");
			exit(1);
			}
    		if (fgets(readbuf, 80, fp)==NULL) {
      			perror("fgets"); 
      			exit(1);} 
	printf("Otrzymany tekst: %s\n", readbuf);}
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

	return 0;
}    
