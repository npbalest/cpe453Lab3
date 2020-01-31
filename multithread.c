
#include <stdlib.h>
#include <stdio.h>
#include <time.h>




int main (int argc, char *argv[]) {

}


//merge sort function used with help from geeksforgeek algorithm
void mergesort(int array[], int left, int right) {
	if (left > right) {
		int middle = left + ((right-1)/2);
		mergesort(array, left, middle);
		mergesort(array, middle+1, right);
		merge(array, left, right, middle);
	}
}

void merge(int array[], int left, int right, int middle) {
	int a, b;
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

