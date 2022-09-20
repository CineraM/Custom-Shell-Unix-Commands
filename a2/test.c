#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUF_LEN 100
#define ARR_LEN 99172

int pstrcmp( const void* a, const void* b )
{
  return strcmp( *(const char**)a, *(const char**)b );
}

int main(int argc, char *argv[])
{
    int param_size = argc - 1;
    FILE *fptr;
    char buf[BUF_LEN];
    static char lines[ARR_LEN][BUF_LEN];    // allocated in memory segment not in stack segment
    int i, j, idx = 0;

    fptr = fopen(argv[1], "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    
    while(fgets(buf, BUF_LEN, fptr)) 
    {
        strncpy(lines[idx], buf, BUF_LEN);
        idx++;
    }
    fclose(fptr);

    size_t n = sizeof(lines) / sizeof(lines[0]);
    // qsort(lines, n, sizeof(lines[0]), pstrcmp);

    for(i=0; lines[i][0]!= '\0'; i++) printf("%s", lines[i]);

    return 0;
}


// function to swap elements
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
int partition(int array[], int low, int high) {
  
  // select the rightmost element as pivot
  int pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
    
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);
    
    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);
    
    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}