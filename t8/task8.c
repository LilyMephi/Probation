#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#define N 10
int A[N][N];
int B[N][N];
int C[N][N];
int count_signals = 0;


volatile int i = 0,j = 0;
void multiply(){
	for(i = 0; i < N; i++)
    		for(j = 0; j < N; j++)
    		{
        		C[i][j] = 0;
        		for(int k = 0; k < N; k++){
        			C[i][j] += A[i][k] * B[k][j];
        		}
        		sleep(1);
    		}
}

void listener(int sig){
	if(sig == SIGINT){
		if(++count_signals == 2){
			exit(1);
			//signal(SIGINT, SIG_DFL);
		}
		printf("Now calculating the element C[%d][%d]",i,j);
		//signal(SIGINT, SIG_DFL);
		
	}
}

int main(int argc, char *argv[])
{
	
	for (i = 0; i < N; i++)
    		for (j = 0; j < N; j++)
    		{
     		   A[i][j] = rand() % 10;
     		   B[i][j] = rand() % 10;
   	 }
   	 struct sigaction sa;
   	 sa.sa_flags = SA_RESTART;
   	 sa.sa_handler = listener;
   	 sigaction(SIGINT,&sa,NULL);
   	//signal(SIGINT,listener); 
   	multiply();
   	raise(SIGINT);
   	raise(SIGINT);
	return 0;
}
