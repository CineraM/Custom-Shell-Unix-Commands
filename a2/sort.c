#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define BUF_LEN 100
#define ARR_LEN 99172


// global variables instead of passing variables as reference to functions
char buf[BUF_LEN];
static char lines[ARR_LEN][BUF_LEN];    // allocated in memory segment not in stack segment
static char eval[ARR_LEN][BUF_LEN]; 
int idx = 0;

// quicksort implementation adapted from:
// https://www.programiz.com/dsa/quick-sort
int partition(int low, int high)
{
    // select the rightmost element
    char pivot[BUF_LEN];
    strncpy(pivot, eval[high], BUF_LEN);
    // pointer for greater element
    int i = low-1;
    
    // traverse each element of the array
    // compare with the pivot
    int j;
    for(j = low; j < high; j++)
    {
        if(strcmp(eval[j], pivot) <= 0)
        {
            i++;
            strncpy(buf, eval[i], BUF_LEN);   
            strncpy(eval[i], eval[j], BUF_LEN);
            strncpy(eval[j], buf, BUF_LEN);

            strncpy(buf, lines[i], BUF_LEN);   
            strncpy(lines[i], lines[j], BUF_LEN);
            strncpy(lines[j], buf, BUF_LEN);
        }
    }

    i++;
    strncpy(buf, eval[i], BUF_LEN);   
    strncpy(eval[i], eval[high], BUF_LEN);
    strncpy(eval[high], buf, BUF_LEN);

    strncpy(buf, lines[i], BUF_LEN);   
    strncpy(lines[i], lines[high], BUF_LEN);
    strncpy(lines[high], buf, BUF_LEN);

    return i;
}

void quick_sort(int low, int high)
{
    if(low < high)
    {
        int pi = partition(low, high);
        quick_sort(low, pi-1);
        quick_sort(pi+1, high);
    }
}

int main(int argc, char *argv[])
{

    // Calculate the time 
    clock_t t;
    t = clock();

    FILE *fptr;
    int i, j;
    
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

    int z, k;
    int eidx = 0;
    int copy_idx = 0;
    memset(buf, 0, BUF_LEN);
    // truncated strings for sorting comparison
    for(i=0; i<=idx; i++)
    {
        // finding alpha, or numeric character index in current string
        for(z=0; z<BUF_LEN; z++)
        {
            if (lines[i][z] >= 48 && lines[i][z] <= 57) break;  // digits
            if (lines[i][z] >= 65 && lines[i][z] <= 90) break;  // cap
            if (lines[i][z] >= 97 && lines[i][z] <= 122) break; // lower
            if (lines[i][z] == '\0') break;
        }
        if(z==BUF_LEN || lines[i][z] == '\0')    // if there is not a numeric || alpha char, copy all the string
        {
            strncpy(buf, lines[i], BUF_LEN);
        }
        else // truncate the string until the desired character
        {
            int copy_idx = 0;
            for(k = z; k<BUF_LEN; k++)
            {
                buf[copy_idx] = lines[i][k];
                copy_idx++;
            }
        }
        // copy the string into eval
        strncpy(eval[eidx], buf, BUF_LEN);
        eidx++; // increase index for next string
        memset(buf, 0, BUF_LEN);
    }

    int n = sizeof(lines)/sizeof(lines[0]);
    quick_sort(0, idx); // idx is the last element int the array
    
    // print the output
    for(i=0; i<=idx; i++) printf("%s", lines[i]);

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // time in seconds
    printf("Run time: %f seconds", time_taken);

    return 0;
}


// int main(int argc, char *argv[])
// {

//     int param_size = argc - 1;
//     FILE *fptr;
//     char buf[BUF_LEN];
//     // static char lines[ARR_LEN][BUF_LEN];    // allocated in memory segment not in stack segment
//     int i, j, idx = 0;

//     char **arr = (char**) calloc(ARR_LEN, sizeof(char*));
    
//     fptr = fopen(argv[1], "r");
//     if (fptr == NULL)
//     {
//         printf("Cannot open file \n");
//         exit(0);
//     }
    
//     while(fgets(buf, BUF_LEN, fptr)) 
//     {
//         // printf("%s", buf);
//         arr[idx] = (char*) calloc(BUF_LEN, sizeof(char));
//         arr[idx] = buf;
//         // printf("%s", arr[idx]);
//         idx++;
//     }
//     fclose(fptr);

//     for(i=0; i<idx; i++)
//     {
//         // printf("%d\n", i);
//         printf("%s\n", arr[i]);
//         free(arr[i]);
//     }
//     return 0;
// }


