#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    // We use two pipes
    // First pipe to send input string from parent
    // Second pipe to send concatenated string from child

    while(1)
    {
        char input_str[100];
        scanf("%s", input_str);

        for(int i = 0; i<4; i++)
        {
            int fd1[2]; // Used to store two ends of first pipe
            int fd2[2]; // Used to store two ends of second pipe

            if (pipe(fd1) == -1) 
            {
                fprintf(stderr, "Pipe Failed");
                return 1;
            }
            if (pipe(fd2) == -1) 
            {
                fprintf(stderr, "Pipe Failed");
                return 1;
            }
            
            pid_t p = fork();

            if (p < 0) 
            {
                fprintf(stderr, "fork Failed");
                return 1;
            }
            else if (p > 0) { // Parent process
                char concat_str[100];

                close(fd1[0]); // Close reading end of first pipe

                // Write input string and close writing end of first pipe.
                printf("parent %s\n", input_str);
                write(fd1[1], input_str, strlen(input_str) + 1);
                close(fd1[1]);

                // Wait for child to send a string
                wait(NULL);

                close(fd2[1]); // Close writing end of second pipe

                // Read string from child, print it and close
                // reading end.
                read(fd2[0], concat_str, 100);
                
                close(fd2[0]);
            }

            // child process
            else {
                close(fd1[1]); // Close writing end of first pipe

                // Read a string using first pipe
                char concat_str[100];

                read(fd1[0], concat_str, 100);
                printf("child %s\n", concat_str);

                // Close both reading ends
                close(fd1[0]);
                close(fd2[0]);

                // Write concatenated string and close writing end
                write(fd2[1], concat_str, strlen(concat_str) + 1);
                close(fd2[1]);

                exit(0);
            }
        }
    }

}

