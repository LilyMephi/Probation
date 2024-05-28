#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1000
int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char *argv[])
{
	if( argc != 4){
		printf("Неверное количество аргументов");
	}
	FILE *fin, *fout;
	if ( (fin = fopen(argv[1],"r")) == NULL){
		printf("НЕ получилось открытьфайл для чтения");
		return -1;
	}
	
	if ( (fout = fopen(argv[2],"w")) == NULL){
		printf("НЕ получилось открытьфайл для записи");
		return -1;
	}
	char *line = NULL;
	size_t len = 0;
        ssize_t read;
        int num_lines = 0;
        
        char *lines[MAX_LINE];
	while(r(ead = getline(&line,&len,fin)) != -1){
		if(!strcmp(line,"\n")) continue;
		lines[num_lines] = strdup(line);
		num_lines++;
	}
	int sort_method = atoi(argv[3]);
	
	switch(sort_method){
		case 1:
			 qsort(lines, num_lines, sizeof(char *), compare);
           		 break;
           	// сюда можно добавить разные виды сортировки
           	default:
           		printf("Невернно виедна название сортировки.");
           		return -1;
	}
	
	for (int i = 0; i < num_lines; i++) {
        	fputs(lines[i], fout);
        	printf("%s", lines[i]);
        	free(lines[i]);
   	 }
    
	fclose(fin);
	fclose(fout);
	return 0;
}
