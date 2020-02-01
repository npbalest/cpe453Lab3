
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <time.h> 

#define NUM_THREADS 2 
#define ARR_SIZE 3000000

void print_list(int array[], int size);
void *sorting(void *param); //Threads call this function

int arr[ARR_SIZE] = {}; //array shared by all threads

void print_list(int array[], int size) 
{ 
    int i; 
    for (i = 0; i < size; i++) 
        printf("%d ", array[i]); 
    printf("\n"); 
} 
  
/* Driver program to test above functions */
int main(int argc, char *argv[]) 
{ 
    int num, i;

    FILE *in;

    in = fopen(argv[1],"r");

    //input numbers from file into array
    while (!feof (in) && fscanf (in, "%d", &num) && i++ < NUM_THREADS){
        arr[i] = num;
    }

    int arr_size = sizeof(arr)/sizeof(arr[0]);

    pthread_t tid[NUM_THREADS]; //thread identifier
    pthread_attr_t attr[NUM_THREADS]; //set of thread attributes

    //initialize all thread attributes
    for (i = 0; i < NUM_THREADS; i++){
        pthread_attr_init(&attr[i]);
    }

    //creates all threads with appropiate arguments
    for (i = 0; i < NUM_THREADS; i++){
        pthread_create(&tid[i], &attr[i], sorting, tid);
    }

    //joins all threads
    for (i = 0; i < NUM_THREADS; i++){
        pthread_join(tid[i], NULL);
    }

    print_list(arr, arr_size); 

    fclose(in);

    return 0; 
}

//Threads will begin control in this function
void *sorting(void *param)
{
    if (pthread_self() == tid[0]) {
        //lower bound
    } else {
        //upper bound
    }

    pthread_exit(0);
}
