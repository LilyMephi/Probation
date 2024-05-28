#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main(int argc, char *argv[])
{
	pid_t pid;
	
	 
	if(argc != 2) {fprintf(stderr,"Wrong arguments!\nUse: ./nameprg <filename>\n"); return -1;}
	
	FILE *fin;
	if((fin = fopen(argv[1],"r")) == NULL){
		fprintf(stderr, " Fail to open file.\n");
                return -1;
	} 
	pid = fork();
	char *line = NULL;
	char *name = NULL;
	size_t len= 0;
        ssize_t read;
        
	if( pid < 0){
		fprintf(stderr,"Fail to create threads!\n "); 
		exit(1);
	}
	FILE *fout;
	if( pid == 0){
		name = "outchaild.txt"; 
	}else{
		name = "outparent.txt";
	}
	if((fout = fopen(name,"w+")) == NULL){
		fprintf(stderr, " Fail to create chaild file.\n");
                return -1;
	}
        while(read = getline(&line,&len,fin) != -1){
		fputs(line, fout);
	}
	fclose(fout);
	if( pid != 0){
		wait(NULL);
	}else{
		exit(1);
	}
		FILE *fch;	
		FILE *fp;
		if((fch = fopen("outchaild.txt","r")) == NULL){
			fprintf(stderr, " Fail to open file.\n");
                	return -1;
		}else{ 
			while(read = getline(&line,&len,fin) != -1){
				printf("%s",line);
			}
		}
		if((fin = fopen("outparent.txt","r")) == NULL){
			fprintf(stderr, " Fail to open file.\n");
                	return -1;
		}else{ 
			while(read = getline(&line,&len,fin) != -1){
				printf("%s",line);
			}
		}	
	
	return 0;
}
