#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


 

int main()

{
 //extern const char *sys_errlist[];
 int p1[2];
 if(pipe(p1) == -1) { return -1; }
 int pid = fork();
 if(pid == -1) { return -1; }
 
 if(pid == 0){
 	//recive process
 	char buf[100];
 	if(read(p1[0], &buf, sizeof(buf)) == -1){
		fprintf(stderr, "Невозможно прочесть\n");
        }
        printf("Recive massage from pid == 1: %s",buf);
 }else{
 	//sending process
 	char buffer[] = " Hello from pid == 0!\n"; 
 	if(write(p1[1],&buffer,sizeof(buffer)) == -1){
 		perror("Невозможно записать");
 		return errno;
 	}
 }
  close(p1[0]);
  close(p1[1]);
  
  int fd_fifo; //дескриптор FIFO
  
  unlink("myfifo");
  
  //Создаем FIFO
  if((mkfifo("myfifo", 0777)) == -1)
  {
    printf("%s\n",strerror(errno));
    return -1;
  }
  
  if((fd_fifo=open("myfifo", O_RDWR)) == - 1)
  {
    //fprintf(stderr, "FAILed to open %s\n",sys_errlist[errno]);
    perror("cannot open fail");
    return -1;
  }
  
  return 0;
} 
