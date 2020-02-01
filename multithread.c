
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 2
#define ARR_SIZE 3000000

void merge(int array[], int left, int right, int middle);
void *sorting(void *param);
int cmpfunc (const void * a, const void * b);
void print_list(int array[], int size);

int arr[ARR_SIZE] = {};
int arr_copy[ARR_SIZE] = {};
int threadpart = 0;

//Driver program
int main(int argc, char* argv[])
{
	FILE *in;
	FILE *out;

	in = fopen(argv[1], "r");
	int i = 0;
	int num;
	int b = 0, c = 0, n = 0; //for threads for loops

	struct timespec start, start_1, finish, finish_1;
	double elapsed, elapsed_1;

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

 //    printf("Number of ints in file (i): %d\n", i); 

	// printf("Given array is \n"); 
 //    print_list(arr, i); 

	pthread_t tid[NUM_THREADS];

    memcpy(arr_copy, arr, i*sizeof(int));
    clock_gettime(CLOCK_MONOTONIC, &start_1); 
	qsort(arr_copy, i, sizeof(int), cmpfunc);
	clock_gettime(CLOCK_MONOTONIC, &finish_1);
	elapsed_1 = (finish_1.tv_sec - start_1.tv_sec);
	elapsed_1 += (finish_1.tv_nsec - start_1.tv_nsec) / 1000000000.0;
	printf("Time for sequential \n");
	printf("%f\n", elapsed_1);


	clock_gettime(CLOCK_MONOTONIC, &start); 

	for (b = 0; b < NUM_THREADS; b++) {
		pthread_create(&tid[b], NULL, sorting, (void*)(intptr_t)i);
	}

	for (c = 0; c < NUM_THREADS; c++) {
		pthread_join(tid[c], NULL);
	}

    // printf("After threads array is \n"); 
    // print_list(arr, i);

    merge(arr, 0, i-1, (i-1)/2);

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

    // printf("After merge \n"); 
    //print_list(arr, i);

    return 0;
} 

//for builtin qsorting 
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

//merge function to merge subarrays
void merge(int array[], int left, int right, int middle) {
	int a = 0, b = 0;
	int i = middle - left + 1;
	int j = right - middle;

	// printf("right: %d\n", right);
	// printf("mid: %d\n", middle);
	// printf("i: %d\n", i); 
	// printf("j: %d\n", j); 

	int temp1[i];
	int temp2[j];

	for (a = 0; a < i; a++) {
		temp1[a] = array[a + left];
	}
	for (b = 0; b < j; b++) {
		temp2[b] = array[b + middle + 1];
	}

    // printf("Temp arrays are: \n"); 
    // print_list(temp1, i);	
    // print_list(temp2, j);

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
	threadpart++;
	if (threadpart == 1) {
		int size = (intptr_t)param;
		// printf("1st half\n");
		if(size % 2 != 0){
			// print_list(arr, size/2+1);
			qsort(arr, size/2+1, sizeof(int), cmpfunc);
		} else {
			// print_list(arr, size/2);
			qsort(arr, size/2, sizeof(int), cmpfunc);
		}
		// printf("1st half sorted\n");
		// if(size % 2 != 0){
		// 	print_list(arr, size/2+1);
		// } else {
		// 	print_list(arr, size/2);
		// }
	}
	else {
		int size = (intptr_t)param;
		// printf("2nd half\n");
		if(size % 2 != 0){
			// print_list(&arr[(size/2)+1], size/2);
			qsort(&arr[(size/2)+1], size/2, sizeof(int), cmpfunc);
		} else {
			// print_list(&arr[size/2], size/2);
			qsort(&arr[size/2], size/2, sizeof(int), cmpfunc);
		}
		// printf("2nd half sorted\n");
		// if(size % 2 != 0){
		// 	print_list(&arr[(size/2)+1], size/2);
		// } else {
		// 	print_list(&arr[size/2], size/2);
		// }
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