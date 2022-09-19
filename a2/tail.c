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
    static char lines[ARR_LEN][BUF_LEN];
    int limit = 10;
    int idx = 0;
    
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

    int i;
    for(i=(idx-limit); i<idx; i++)
    {
        printf("%s", lines[i]);
    }

    return 0;
}
