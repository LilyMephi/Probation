#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


 

int main()

{
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
 	if(write(p1[1],&buffer,strlen(buffer)) == -1){
 		fprintf(stderr, "Невозможно записать\n");
 	}
 }
 
 /*
  int fd_fifo; //дескриптор FIFO
  
  char buffer[]="Текстовая строка для fifo\n";
  char buf[100];
  
  unlink("myfifo");

  //Создаем FIFO
  if((mkfifo("myfifo", 0777)) == -1)
  {
    fprintf(stderr, "Невозможно создать fifo\n");
    return -1;
  }
	
  //Открываем fifo для чтения и записи
  printf("Opening ...\n");
  if((fd_fifo=open("myfifo", O_RDWR)) == - 1)
  {
    fprintf(stderr, "Невозможно открыть fifo\n");
    return -1;
  }
  printf("Open");
  write(fd_fifo,buffer,strlen(buffer)) ;

  if(read(fd_fifo, &buf, sizeof(buf)) == -1){
	fprintf(stderr, "Невозможно прочесть из FIFO\n");
  }else{
  	printf("Прочитано из FIFO : %s\n",buf);
  }	
  close(fd_fifo);*/
  close(p1[0]);
  close(p1[1]);
  return 0;
} 
