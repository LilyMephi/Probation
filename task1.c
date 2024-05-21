#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define N 16
#define NTREADS 2

//создаем массив который мудем сортировать
int arr[N];

typedef struct{
	int left;
	int right;
} Range;

// слияние двух массивов
void merge(int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// функция которая будет сортировать слиянем в threads
void * mergeSort(void * arg) {
   Range *r = (Range *)arg;
   int left = r->left;
   int right = r->right;
   int mid = left + (right -left)/2;
   if( left < right){
   	//разделяем массив на подмасивы пополам
   	Range Rleft = {left, mid};
   	Range Rright = {mid + 1, right};
   	mergeSort(&Rleft);
   	mergeSort(&Rright);
   	
   	merge(left,mid,right);
   	
   }
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t tid[NTREADS]; // идентификатор потока 
	Range r[NTREADS]; // создаем для каждого потока свой ранг для массива
	int size = N / NTREADS; // размер массива в каждом потоке

	// заполняем массив рандомными значениями
  	for(int i = 0; i < N; ++i){
  		arr[i] = rand()%100;
  		printf("%d ",arr[i]);
  	} 
  	printf("\n");
	
	for(int i = 0; i < NTREADS; ++i){
		r[i].left = i*size;
		r[i].right = (i+1)*size - 1;
		//создаем новый поток
		if(pthread_create(&tid[i],NULL,mergeSort,&r[i]) != 0) { 
			perror("Failed to create thread");
		}
	} 
	for(int i = 0; i < N/2; ++i){
		//Ждем окончание работы потока
		if(pthread_join(tid[i],NULL) != 0) { perror("Failed to join thread");}
		}
	// соединаям отсортированные по потокам части массива
	Range rf = {0, N-1};
  	mergeSort(&rf);
  	
  	//выводим отсортированный массив
  	for(int i = 0; i < N; ++i){
  		printf("%d ",arr[i]);
  	}
  	printf("\n");
  	return 0;
}
