#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // skip the 1st command
    int param_size = argc - 1;

    // store the 1st command and the list of parameters
    char* cmd = argv[1];
    char* parameters[param_size+1];

    // copy the parameters into the string
    int i;
    for(i = 0; i < param_size; i++)
        parameters[i] = argv[1+i];

    // terminate the parameter string
    parameters[param_size] = NULL;

    // create the child process
    int new_process = fork();

    if(new_process < 0)
    {
        fprintf(stderr, "Fork Failed\n");
        exit(1);
    }
    else if(new_process == 0)
    {
        // child process, execute cmd params in here
        int status_code = execvp(cmd , parameters);
        if(status_code == -1)
        {
            printf("Process Failed\n");
            exit(1);
        }
    }
    else
    {
        // wait for the children process to finish
        wait(NULL);
        printf("------------------------------\n");
    }

    return 0;
}
