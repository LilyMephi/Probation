#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>


int main(int argc, char *argv[])
{
	if(argc != 2) {printf("Wrong arguments!\n Use: ./nameprg <filename>\n"); return 1;}
	
	char *date;
	int ret;
	struct stat sb;
	
	if ((ret = stat(argv[1], &sb))!=0)
          {
            fprintf(stderr, " Stat failure error %d.\n %s", ret,strerror(errno));
            return -1;
          }
          
       if (S_ISREG(sb.st_mode)) {
       		printf("Regular file\n");	
       }
	
	if (S_ISDIR(sb.st_mode)) {
       		printf("Directory\n");	
       }
       
       if (S_ISCHR(sb.st_mode)) {
       		printf("character device\n");	
       }
       
         if (S_ISFIFO(sb.st_mode)) {
       		printf("FIFO file\n");	
       }
       
       if(sb.st_mode & S_IRWXU){
       		printf("User has all rights\n");
       }
       
       if(sb.st_mode & S_IRUSR){l
       		printf("User can read\n");
       }
       
       if(sb.st_mode & S_IWUSR){
       		printf("User can write\n");
       }
       
       if(sb.st_mode & S_IXUSR){
       		printf("User can execute\n");
       }
       
       printf("Size: %ld byte\n", sb.st_size);
       char time_str[100];
       strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&(sb.st_mtim.tv_sec)));
       printf("Time of last modification %s\n", time_str);
       
       
	
	
	return 0;
}
