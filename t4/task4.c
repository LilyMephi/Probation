/*Написать парсер аргументов командной строки на языке С (getopt и
getopt_long). Программа принимает опции -m -c -s -t, а также
--elbrus=[1c+, 2c+, 2c3, 4c, 8c, 16c] и любое количество строк не-опций (без
символов - и -- перед ними).*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#define MAX_SIZE 1024

int eoption(char * str){
	char * option[] = {"1c+", "2c+", "2c3", "4c", "8c", "16c"};
	for (int i = 0; i < 6; ++i){
		if(strcmp(str,option[i]) == 0) return 0;
	}
	return -1;
}
int main(int argc, char *argv[])
{
	int flag = 0;	
	char stropt[MAX_SIZE] = "Options are correct: ";
	char strnonopt[MAX_SIZE] = "non-options: ";
	int rez;
	int option_index = 0;
	const char* short_options = "mcst";
	const struct option long_options[] = {{"elbrus", required_argument,NULL,'e'},{0,0,0,0}};
	while (1){
		rez = getopt_long(argc, argv,short_options, long_options, &option_index);
		if(argc == 1) {printf("Without option!\n"); return 0;}
		if(rez == -1) break;
		switch (rez){
			case 'm': strcat(stropt,"m, ");
				  break;
			case 't': strcat(stropt,"t, "); 
				  break;
			case 'c': strcat(stropt,"c, ");
				break;
			case 's': strcat(stropt,"s, ");
				 break;
			case 'e': if(eoption(optarg) == 0){
					strcat(stropt,long_options[option_index].name);
					strcat(stropt,"=");
					strcat(stropt,optarg);
					strcat(stropt,", ");
					break;
				  }else{ flag = -1; break;}
			case ':': flag = -1; break;
			case '?': flag = -1; break;
			default: abort();
		}
	}
	if (optind < argc)
        {        	
      		while (optind < argc){
      		
       			strcat(strnonopt, argv[optind++]);
       			strcat(strnonopt, " ,");
       			}
       		strnonopt[strlen(strnonopt)-1] = 0;
       		strcat(strnonopt, ".");
 
   	}else{
   		strcat(stropt, "non.");
   	}
   	if(flag == 0){
   		printf("%s %s\n", stropt,strnonopt);
   	}else{
   		printf("Options are incorrect.\n");
   	}
	return 0;
	
	
}

//printf("%d --%s=%s",eoption(optarg),long_options[option_index].name,optarg); break;
