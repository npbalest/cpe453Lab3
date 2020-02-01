
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define NUM_THREADS 2
#define ARR_SIZE 20

void merge(int array[], int left, int right, int middle);
void *sorting(void *param);
int cmpfunc (const void * a, const void * b);
void print_list(int array[], int size);

int arr[ARR_SIZE] = {};
int threadpart = 0;

//Need to do
//dup so you can compare both runtimes
//find arr to put in with fgets


//Driver program
int main(int argc, char* argv[])
{
	FILE *in;
	FILE *out;

	in = fopen(argv[1], "r");
	int i = 0;
	int num;
	int b = 0, c = 0; //for threads for loops

	if (in == NULL) {
		printf("No file to read in.");
	}
	else {
		while ((fscanf(in, "%d", &num) != EOF) && (i < ARR_SIZE)) {
			arr[i] = num;
			i++;
		}
		fclose(in);
	}

	printf("Given array is \n"); 
    print_list(arr, i); 

	pthread_t tid[NUM_THREADS];


	for (b = 0; b < NUM_THREADS; b++) {
		pthread_create(&tid[b], NULL, sorting, (void*)(intptr_t)i);
	}

	for (c = 0; c < NUM_THREADS; c++) {
		pthread_join(tid[c], NULL);
	}

    printf("After threads array is \n"); 
    print_list(arr, i);

    merge(arr, 0, i, i/2);

    printf("After merge \n"); 
    print_list(arr, i);

    return 0;
} 

//for builtin qsorting 
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void merge(int array[], int left, int right, int middle) {
	int a = 0, b = 0;
	int i = middle - left + 1;
	int j = right - middle;

	int temp1[i];
	int temp2[j];

	for (a = 0; a < i; a++) {
		temp1[a] = array[a + left];
	}
	for (b = 0; b < j; b++) {
		temp2[b] = array[b + middle + 1];
	}

	a = 0;
	b = 0;
	int c = left;

	while ((a < i) && (b < j)) {
		if (temp1[a] <= temp2[b]) {
			array[c] = temp1[a];
			a++;
		}
		else {
			array[c] = temp2[b];
			b++;
		}
		c++;
	}
	while (a < i) {
		array[c] = temp1[a];
		a++;
		c++;
	}
	while (b < j) {
		array[c] = temp2[b];
		b++;
		c++;
	}
}


void *sorting(void *param) {
	int size = (intptr_t)param;
	threadpart++;
	if (threadpart == 1) {
		printf("1st half\n");
		print_list(arr, size/2);
		qsort(arr, size/2, sizeof(int), cmpfunc);
		printf("1st half sorted\n");
		print_list(arr, size/2);
	}
	else {
		printf("2nd half\n");
		print_list(&arr[size/2], size/2);
		qsort(&arr[size/2], size/2, sizeof(int), cmpfunc);
		printf("2nd half sorted\n");
		print_list(&arr[size/2], size/2);
	}
	pthread_exit(0);
}

//want to print list to view
void print_list(int array[], int size) { 
    int i; 
    for (i = 0; i < size; i++) 
        printf("%d ", array[i]); 
    printf("\n"); 
} 