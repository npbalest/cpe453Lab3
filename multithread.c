#include <stdlib.h>
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
int *first_half;
int *second_half;
int threadpart = 1;


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
    int g, h, f; //for splitting arrays

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
    //printf("%d\n", i);

    printf("Given array is \n"); 
    print_list(arr, i); 

    first_half = (int *)calloc((i/2), sizeof(int));
    second_half = (int *)calloc((i/2), sizeof(int));

    if(first_half == NULL) {
      printf("first malloc of size %d failed!\n", i);   // could also call perror here
      exit(1);   // or return an error to caller
    }

    if(second_half == NULL) {
      printf("second malloc of size %d failed!\n", i);   // could also call perror here
      exit(1);   // or return an error to caller
    }

    while (g != i) {
        //get first half of array
        if (f < (i / 2)) {
            first_half[f] = arr[f];
            f++;
        } //second half
        else {
            second_half[h] = arr[f];
            h++;
            f++;
        }
        g++;
    }
    print_list(first_half, f);
    print_list(second_half, h);

    pthread_t tid[NUM_THREADS];

    int b = 0;
    int c = 0;

    for (b = 0; b < NUM_THREADS; b++) {
        pthread_create(&tid[b], NULL, sorting, NULL);
    }

    for (c = 0; c < NUM_THREADS; c++) {
        pthread_join(tid[c], NULL);
    }

    printf("\nSorted array is \n"); 
    print_list(arr, i);
  
/*
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    qsort(arr, 6, sizeof(int), cmpfunc);*/
    return 0;
} 


void *sorting(void *param) {
    if (threadpart == 1) {
        threadpart++;
        qsort(first_half, ( sizeof(first_half)/sizeof(first_half[0]) ), sizeof(int), cmpfunc);
    }
    else {
        qsort(second_half, ( sizeof(second_half)/sizeof(second_half[0])), sizeof(int), cmpfunc);
    }
    pthread_exit(0);
}


//for builtin qsorting 
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

//want to print list to view
void print_list(int array[], int size) { 
    int i; 
    for (i = 0; i < size; i++) 
        printf("%d ", array[i]); 
    printf("\n"); 
} 