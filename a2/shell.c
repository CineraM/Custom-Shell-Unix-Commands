#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUF_LEN 150

char commands[8][15] = {"cat", "head", "tail", "ls", "sort", "grep", "sed"};
static char welcome[1134] = "⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀\n⡇   Matias Cinera - U 6931_8506    ⢰\n⡇   COP 6611                       ⢰\n⡇   Instructor: Dr. Ankur Mali     ⢸\n⡇   Assigment 2 - Part 1           ⢸\n⣇⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣠\n⠉⠉⠉⠉⠉⣽⠏⣽⡿⣻⣿⣯⡍⣉⠉⣉⣽⠿⠿⠿⡫⣷⣩⣭⣍⠺⣏⠉⠉⠉⠁\n⠀⠀⠀⠀⠀⡟⢰⣿⠗⣉⠤⠄⠈⠽⢿⣩⠤⢒⡶⠖⣚⣛⣛⣟⣿⣆⢱⡄⠀⠀⠀\n⠀⠀⠀⠀⠀⡇⢸⡇⠘⠁⢀⡤⡲⡿⣿⣖⠒⢥⠔⢫⣿⣟⣷⠈⢻⡾⢸⡇⠀⠀⠀\n⠀⠀⠀⠀⠀⡇⠸⡇⠐⠒⢵⡊⠀⣷⣻⣾⣧⠾⠤⠬⠿⠛⢛⣿⣿⡇⢸⡇⠀⠀⠀\n⠀⠀⠀⠀⠀⡇⠀⣧⢠⠔⢒⣚⠛⠯⠭⠤⠤⠤⠤⠖⣒⣊⡭⢴⣿⠃⢸⡇⠀⠀⠀\n⠀⠀⠀⠀⠀⣇⠀⢿⡈⠑⠲⠭⠭⢭⣉⣉⣉⣉⡭⠭⠭⠴⢖⡟⠁⣀⡾⠃⠀⠀⠀\n⠀⠀⠀⠀⠀⢿⡄⠈⢻⡶⢤⣀⣀⣀⣀⣀⣀⣀⣀⣤⠴⠚⠋⣷⡞⠋⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⢈⣿⣦⣰⠇⠀⠀⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣂⠀⠀⠀⠀⠀";

static char args[50][BUF_LEN];
static char extract[5][BUF_LEN];

char file_name[30];

int main()
{
    char buf[BUF_LEN];
    system("clear");    
    printf("%s\n$ ", welcome);

    // active loop for input
    while(1)
    {
        // get std line
        char *input = NULL;
        size_t size;
        
        if (getline(&input, &size, stdin) == -1) 
            continue; // error
        
        // continue if its a new line
        if(input[0]=='\n') // just a new input
        {
            printf("$ ");
            continue;
        }
        
        // scan the 1st commmand
        int i;
        memset(buf, 0, BUF_LEN);
        for(i=0; input[i] != '\0'; i++)
        {
            if(input[i] == ' ' || input[i] == '\n') break;
            buf[i] = input[i];
        }
        buf[i] = '\0';
        
        int flag = 0;
        if(strcmp(buf, "exit") == 0) // exit program
            break;
        else if(strcmp(buf, "clear") == 0)
        {
            system("clear"); // allow clear for debugging purpuses
            printf("$ ");
            continue;
        } 
        else
        {
            for(i=0; i<7; i++)  // check if the command is valid
            {
                if(strcmp(buf, commands[i]) == 0)
                {
                    flag=1;
                    break;  
                }
            }
        }

        if(!flag)   // get new line if command is invalid
        {
            printf("Command '%s' not supported\n$ ", buf);
            continue;
        }

        // clear args before storing them
        memset(args, 0, sizeof(args[0][0]) * 50 * BUF_LEN);
        int count = 0;
        int idx = 0;
        for(i=0; input[i] != '\0'; i++)
        {
            if(input[i] == '|' || input[i] == '-')
            {
                args[idx][count+1] = '\0';
                count=0;
                idx++;
                continue;
            }
            // if first index is a space
            if(count == 0)
            {
                if(input[i] == ' ')
                    continue;
            }
            if(input[i] == '\n') continue;

            args[idx][count] = input[i];
            count++;
        }
        args[idx][count+1] = '\0';

        char exec[154] = "./";
        strcat(exec, args[0]);

        if(idx == 0)
        {
            printf("\n$ ");
            system(exec);
            continue; // only one command to execute
        }
        else
        {
            // clear both buffers
            remove("buffer_file2.txt");
            remove("buffer_file.txt");
            char out[30] = "> buffer_file.txt";
            strcat(exec, out);
            system(exec);
        }

        for(i = 1; i<=idx; i++)
        {
            int fd1[2]; // Used to store two ends of first pipe

            if (pipe(fd1) == -1) 
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

                if(!flag) break;    // teachnically not needed, could possibly avoid bugs
                char concat_str[100];

                close(fd1[0]); // Close reading end of first pipe

                // Write input string and close writing end of first pipe.
                write(fd1[1], args[i], strlen(args[i]) + 1);
                close(fd1[1]);

                // Wait for child to send a string
                wait(NULL);
            }
            else // child process
            {
                close(fd1[1]); // Close writing end of first pipe

                char exec[200] = "./";
                char read_file[30];
                char write_file[30];
                
                if(access("buffer_file.txt", F_OK) == 0)    // file exists
                {
                    strcpy(read_file, "buffer_file.txt");
                    strcpy(write_file, "buffer_file2.txt"); 
                }
                else
                {
                    strcpy(read_file, "buffer_file2.txt");
                    strcpy(write_file, "buffer_file.txt"); 
                }

                // Read a string using first pipe
                char command[100];
                read(fd1[0], command, 100);// read the command from pipe

                int i, flag = 0;
                for(i=0; command[i]!='\0'; i++)
                {
                    if(command[i] == '>')
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag)
                {
                    strcat(exec, command);     // append the command
                    strcat(exec, " ");
                    strcat(exec, read_file);  // append write file
                }
                else
                {
                    strcat(exec, command);     // append the command
                    strcat(exec, " ");
                    strcat(exec, read_file);  // append write file
                    strcat(exec, " >");
                    strcat(exec, write_file);  // append write 
                }

                system(exec);
                remove(read_file);
                // Close both reading ends
                close(fd1[0]);
                exit(0);
            }
        }
        free(input);
        printf("$ ");
    }
    system("clear");
    return 0;
}