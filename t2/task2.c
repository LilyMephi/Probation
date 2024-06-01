#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


 

int main()

{
 int p1[2];// chaild to parent
 int p2[2];//parent to chaild
 if(pipe(p1) == -1) { return -1; }
 if(pipe(p2) == -1) { return -1; }
 int pid = fork();
 if(pid == -1) { return -1; }
 
 if(pid == 0){
 	//chaild process
 	close(p1[0]);
 	close(p2[1]);
 	char buf[] = "Привет из дочернего процесса";
 	char buffer[100];
 	if(read(p2[0], &buffer, sizeof(buffer)) == -1){
		fprintf(stderr, "Невозможно прочесть\n");
        }
        printf("Принято сообщение  от родительского процесса : \"%s\"\n",buf);
        if(write(p1[1],&buf,strlen(buf)) == -1){
 		fprintf(stderr, "Невозможно записать\n");
 	}
 	close(p1[1]);
 	close(p2[0]);
 	//exit(1);
 }else{
 	//parent process
 	close(p1[1]);
 	close(p2[0]);
 	char buf[] = " Привет из родительского процесса"; 
 	char buffer[100];
 	if(write(p2[1],&buf,strlen(buf)) == -1){
 		fprintf(stderr, "Невозможно заmakписать\n");
 	}
 	if(read(p1[0], &buffer, sizeof(buffer)) == -1){
		fprintf(stderr, "Невозможно прочесть\n");
        }
        printf("Принято сообщение  от дочернего процесса : \"%s\"\n",buf);
        close(p1[0]);
 	close(p2[1]);
        wait(NULL);
 }
 
  return 0;
} 
