#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUF_LEN 100

int main(int argc, char *argv[])
{
    // skip the 1st command
    int param_size = argc - 1;
    FILE *fptr;
    char buf[BUF_LEN];
    int limit = 10;
    int count = 0;
    
    
    fptr = fopen(argv[1], "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    
    while(fgets(buf, BUF_LEN, fptr)) 
    {
        if(count==limit) break;
        printf("%s", buf);
        count++;
    }

    fclose(fptr);

    return 0;
}
