#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define N 10

void merge(int arr[], int left, int mid, int right) {
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

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main(int argc, char *argv[])
{

	/*pthread_t tid; // идентификатор потока 
	 pthread_attr_t attr; // отрибуты потока
	
	// получаем дефолтные значения атрибутов 
  	pthread_attr_init(&attr);
  	
  	pthread_exit(0);*/
  	srand(time(NULL));
  	int arr[N];
  	for(int i = 0; i < N; ++i){
  		arr[i] = rand()%100;
  		printf("%d ",arr[i]);
  	}
  	printf("\n");
  	mergeSort(arr, 0, N - 1);
  	for(int i = 0; i < N; ++i){
  		printf("%d ",arr[i]);
  	}
  	printf("\n");
  	//pthread_exit(0);
}
