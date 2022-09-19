#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUF_LEN 100
#define ARR_LEN 99172


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

    char temp[BUF_LEN];
    for(i=0; i<idx; i++)
    {
        for(j=i+1; j<idx; j++)
        {
            if(strcmp(lines[i], lines[j]) > 0)
            {
                strncpy(temp, lines[i], BUF_LEN);   
                strncpy(lines[i], lines[j], BUF_LEN);
                strncpy(lines[j], temp, BUF_LEN);
            }
        }
    }
    for(i=0; lines[i][0]!= '\0'; i++) printf("%s", lines[i]);

    return 0;
}


/*
    char **arr = (char**) calloc(ARR_LEN, sizeof(char*));
    
    fptr = fopen(argv[1], "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    
    while(fgets(buf, BUF_LEN, fptr)) 
    {
        // printf("%s", buf);
        arr[idx] = (char*) calloc(BUF_LEN, sizeof(char));
        arr[idx] = buf;
        // printf("%s", arr[idx]);
        idx++;
    }
    fclose(fptr);

    for(i=0; i<idx; i++)
    {
        // printf("%d\n", i);
        printf("%s\n", arr[i]);
    }
*/