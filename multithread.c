
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 2
#define ARR_SIZE 300

void merge(int array[], int left, int right, int middle);
void *sorting(void *param);
int cmpfunc (const void * a, const void * b);
void print_list(int array[], int size);

int arr[ARR_SIZE] = {};
int arr_copy[ARR_SIZE] = {};
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
	int n = 0;

	struct timespec start, start_1, finish, finish_1;
	double elapsed, elapsed_1; 

	pthread_t tid[NUM_THREADS];

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
	//printf("Given array is \n"); 
    //print_list(arr, i);

    memcpy(arr_copy, arr, i*sizeof(int));

    clock_gettime(CLOCK_MONOTONIC, &start_1); 
	qsort(arr_copy, i, sizeof(int), cmpfunc);
	clock_gettime(CLOCK_MONOTONIC, &finish_1);
	elapsed_1 = (finish.tv_sec - start.tv_sec);
	elapsed_1 += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("Time for sequential \n");
	printf("%f\n", elapsed_1);

	clock_gettime(CLOCK_MONOTONIC, &start); 
	for (b = 0; b < NUM_THREADS; b++) {
		pthread_create(&tid[b], NULL, sorting, (void*)(intptr_t)i);
	}

	for (c = 0; c < NUM_THREADS; c++) {
		pthread_join(tid[c], NULL);
	}
    merge(arr, 0, (i-1), (i-1)/2);
	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("Time for multithreading \n");
	printf("%f\n", elapsed);	

	out = fopen("answer.txt", "w");
	for(n = 0; n < i; n++) {
		fprintf(out,"%d ",arr[n]);
	}
	fclose(out);

    //printf("After merge \n"); 
    //print_list(arr, i);

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
		//printf("1st half\n");
		//print_list(arr, size/2);
		qsort(arr, size/2, sizeof(int), cmpfunc);
		//printf("1st half sorted\n");
		//print_list(arr, size/2);
	}
	else {
		//printf("2nd half\n");
		//print_list(&arr[size/2], size/2);
		qsort(&arr[size/2], size/2, sizeof(int), cmpfunc);
		//printf("2nd half sorted\n");
		//print_list(&arr[size/2], size/2);
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