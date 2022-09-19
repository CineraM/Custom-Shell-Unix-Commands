#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUF_LEN 100

int main(int argc, char *argv[])
{
    FILE *fptr;
    int param_size = argc - 1;

    char buf[BUF_LEN];
    char compare[BUF_LEN];
    strncpy(compare, argv[1], BUF_LEN);
    
    fptr = fopen(argv[2], "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    
    while(fgets(buf, BUF_LEN, fptr)) 
    {
        // print when the substs exists
        if(strstr(buf, compare) != NULL)
            printf("%s", buf);
    }
    fclose(fptr);

    return 0;
}
