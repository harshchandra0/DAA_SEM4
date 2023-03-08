#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int ccounter;

void merge(int arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {
    	ccounter++;
        if (L[i] <= R[j]) 
        {
            arr[k] = L[i];
            i++;
        }
        else 
        {
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

    while (j < n2) 
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
  
void mergeSort(int arr[],int l, int r){
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
  
        merge(arr, l, m, r);
    }
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[low];    // first element as pivot.
    int i = low - 1, j = high + 1;
 
    while (true) {
    
        do {
            i++;
            ccounter++;
        } while (arr[i] < pivot);
 
        do {
            j--;
            ccounter++;
        } while (arr[j] > pivot);
 
        if (i >= j)
            return j;
 
        swap(&arr[i], &arr[j]);
    }
}

 
void quickSort(int arr[], int low, int high){
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


int main(){

  FILE *fptr;
  int n = 100000;
  fptr = fopen("randomm.txt", "w");
  if (fptr == NULL){
    printf("ERROR Creating File!");
    exit(1);
  }

  
  srand(time(0));
  for (int i = 1; i <= n; i++){
    int r = rand() % 100;
    fprintf(fptr, "%d\n", r);
  }
  fclose(fptr);
  

  int block = 1;
  printf("Block\tMerge-comparisons Quick-comparisons\n");
  for (int i = 100; i <= n; i += 100){
    fptr = fopen("randomm.txt", "r");
    int arr[i];

    for (int j = 0; j < i; j++){
      fscanf(fptr, "%d", &arr[j]);
    }
    clock_t t;
    t = clock();
    ccounter=0;
    mergeSort(arr,0,i-1);    // merge sort
    t = clock() - t;
    double time_takenms = ((double)t) / CLOCKS_PER_SEC;
    int mcounter=ccounter;
    fclose(fptr);

    fptr = fopen("randomm.txt", "r");
    int arr2[i];
    for (int j = 0; j < i; j++){
      fscanf(fptr, "%d", &arr2[j]);
    }
    clock_t t2;
    t2 = clock();
    ccounter=0;
    quickSort(arr2,0,i-1);    // quick sort
    t2 = clock() - t2;
    double time_takenqs = ((double)t2) / CLOCKS_PER_SEC;
    int qcounter=ccounter;
	fclose(fptr);
	
	fptr = fopen("randomm.txt", "r");
    int arr3[i];
    for (int j = 0; j < i; j++){
      fscanf(fptr, "%d", &arr3[j]);
    }
	fclose(fptr);
	
    printf("%d\t%d\t\t\t%d\n", block, mcounter, qcounter);
    block++;

  }
  return 0;
}
