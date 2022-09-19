#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    FILE *fptr; // file pointer
    char buf;     // temp character
    int param_size = argc - 1;

    if(param_size == 0)
    {
        printf("No file name provided \n");
        exit(0);
    }
    
    fptr = fopen(argv[1], "r"); // read the file
    if (fptr == NULL)           // exit if file does not exist
    {
        printf("Cannot open file '%s' \n", argv[1]);
        exit(0);
    }

    buf = fgetc(fptr);
    while (buf != EOF)
    {
        printf ("%c", buf);
        buf = fgetc(fptr);
    }

    fclose(fptr);

    return 0;
}
