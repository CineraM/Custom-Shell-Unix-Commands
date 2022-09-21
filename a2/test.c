#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUF_LEN 150

char commands[8][15] = {"cat", "head", "tail", "ls", "sort", "grep", "sed"};
static char welcome[1134] = "⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀\n⡇   Matias Cinera - U 6931_8506    ⢰\n⡇   COP 6611                       ⢰\n⡇   Instructor: Dr. Ankur Mali     ⢸\n⡇   Assigment 2 - Part 1           ⢸\n⣇⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣠\n⠉⠉⠉⠉⠉⣽⠏⣽⡿⣻⣿⣯⡍⣉⠉⣉⣽⠿⠿⠿⡫⣷⣩⣭⣍⠺⣏⠉⠉⠉⠁\n⠀⠀⠀⠀⠀⡟⢰⣿⠗⣉⠤⠄⠈⠽⢿⣩⠤⢒⡶⠖⣚⣛⣛⣟⣿⣆⢱⡄⠀⠀⠀\n⠀⠀⠀⠀⠀⡇⢸⡇⠘⠁⢀⡤⡲⡿⣿⣖⠒⢥⠔⢫⣿⣟⣷⠈⢻⡾⢸⡇⠀⠀⠀\n⠀⠀⠀⠀⠀⡇⠸⡇⠐⠒⢵⡊⠀⣷⣻⣾⣧⠾⠤⠬⠿⠛⢛⣿⣿⡇⢸⡇⠀⠀⠀\n⠀⠀⠀⠀⠀⡇⠀⣧⢠⠔⢒⣚⠛⠯⠭⠤⠤⠤⠤⠖⣒⣊⡭⢴⣿⠃⢸⡇⠀⠀⠀\n⠀⠀⠀⠀⠀⣇⠀⢿⡈⠑⠲⠭⠭⢭⣉⣉⣉⣉⡭⠭⠭⠴⢖⡟⠁⣀⡾⠃⠀⠀⠀\n⠀⠀⠀⠀⠀⢿⡄⠈⢻⡶⢤⣀⣀⣀⣀⣀⣀⣀⣀⣤⠴⠚⠋⣷⡞⠋⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⢈⣿⣦⣰⠇⠀⠀⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣂⠀⠀⠀⠀⠀";

char test_args[3][BUF_LEN] = {"ONE", "TWO", "THREE"};   // testing delete later!
static char args[50][BUF_LEN];

int main()
{
    char buf[BUF_LEN];
    
    system("clear");    
    printf("%s", welcome);

    while(1)
    {
        printf("\n$ ");
        
        // get std line
        char *input = NULL;
        size_t size;
        
        if (getline(&input, &size, stdin) == -1) 
            continue; // no line
        
        // continue if its a new line
        if(input[0]=='\n') // just a new input
            continue;
        
        int i;
        memset(buf, 0, BUF_LEN);
        for(i=0; input[i] != '\0'; i++)
        {
            if(input[i] == ' ' || input[i] == '\n') break;
            buf[i] = input[i];
        }
        buf[i] = '\0';

        char exec[154] = "./";
        strcat(exec, input);
        

        int flag = 0;
        if(strcmp(buf, "exit") == 0) exit(1);
        else if(strcmp(buf, "clear") == 0) system("clear"); // allow clear for debugging purpuses
        else
        {
            for(i=0; i<7; i++)  // check if the command is allowed
            {
                if(strcmp(buf, commands[i]) == 0)
                {
                    flag=1;
                    break;
                }
            }

        }

        if(flag)
        {
            system(exec);
        }
        else
        {
            printf("Command '%s' not supported", buf);
        }
        
        for(int i = 0; i<3; i++)
        {
            int fd1[2]; // Used to store two ends of first pipe
            // int fd2[2]; // Used to store two ends of second pipe

            if (pipe(fd1) == -1) 
            {
                fprintf(stderr, "Pipe Failed");
                return 1;
            }
            // if (pipe(fd2) == -1) 
            // {
            //     fprintf(stderr, "Pipe Failed");
            //     return 1;
            // }
            
            pid_t p = fork();

            if (p < 0) 
            {
                fprintf(stderr, "fork Failed");
                return 1;
            }
            else if (p > 0) { // Parent process

                if(!flag) break;    // if there is an invalid command

                char concat_str[100];

                close(fd1[0]); // Close reading end of first pipe

                // Write input string and close writing end of first pipe.
                // printf("parent %s\n", exec);
                write(fd1[1], test_args[i], strlen(test_args[i]) + 1);
                close(fd1[1]);

                // Wait for child to send a string
                wait(NULL);

                // close(fd2[1]); // Close writing end of second pipe

                // // Read string from child, print it and close
                // // reading end.
                // read(fd2[0], concat_str, 100);
                
                // close(fd2[0]);
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
                // close(fd2[0]);

                // // Write concatenated string and close writing end
                // write(fd2[1], concat_str, strlen(concat_str) + 1);
                // close(fd2[1]);

                exit(0);
            }
        }
        free(input);
    }

    return 1;
}