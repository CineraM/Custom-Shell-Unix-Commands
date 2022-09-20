#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUF_LEN 150

char commands[8][15] = {"cat", "head", "tail", "test", "ls", "sort", "grep", "sed"};
static char welcome[1134] = "⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀\n⡇   Matias Cinera - U 6931_8506    ⢰\n⡇   COP 6611                       ⢰\n⡇   Instructor: Dr. Ankur Mali     ⢸\n⡇   Assigment 2 - Part 1           ⢸\n⣇⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣠\n⠉⠉⠉⠉⠉⣽⠏⣽⡿⣻⣿⣯⡍⣉⠉⣉⣽⠿⠿⠿⡫⣷⣩⣭⣍⠺⣏⠉⠉⠉⠁\n⠀⠀⠀⠀⠀⡟⢰⣿⠗⣉⠤⠄⠈⠽⢿⣩⠤⢒⡶⠖⣚⣛⣛⣟⣿⣆⢱⡄⠀⠀⠀\n⠀⠀⠀⠀⠀⡇⢸⡇⠘⠁⢀⡤⡲⡿⣿⣖⠒⢥⠔⢫⣿⣟⣷⠈⢻⡾⢸⡇⠀⠀⠀\n⠀⠀⠀⠀⠀⡇⠸⡇⠐⠒⢵⡊⠀⣷⣻⣾⣧⠾⠤⠬⠿⠛⢛⣿⣿⡇⢸⡇⠀⠀⠀\n⠀⠀⠀⠀⠀⡇⠀⣧⢠⠔⢒⣚⠛⠯⠭⠤⠤⠤⠤⠖⣒⣊⡭⢴⣿⠃⢸⡇⠀⠀⠀\n⠀⠀⠀⠀⠀⣇⠀⢿⡈⠑⠲⠭⠭⢭⣉⣉⣉⣉⡭⠭⠭⠴⢖⡟⠁⣀⡾⠃⠀⠀⠀\n⠀⠀⠀⠀⠀⢿⡄⠈⢻⡶⢤⣀⣀⣀⣀⣀⣀⣀⣀⣤⠴⠚⠋⣷⡞⠋⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⢈⣿⣦⣰⠇⠀⠀⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣂⠀⠀⠀⠀⠀";

int main()
{
    system("clear");    
    printf("%s", welcome);
    char buf[BUF_LEN];

    // handle input
    while(1)
    {
        printf("\n$ ");
        char *input = NULL;
        size_t size;
        if (getline(&input, &size, stdin) == -1) 
            continue; // no line

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
        
        if(strcmp(buf, "exit") == 0)
            exit(1);
        else if(strcmp(buf, "clear") == 0)
            system("clear");                // allow clear for debugging purpuses
        else
        {
            int i, flag = 1;
            for(i=0; i<8; i++)
            {
                if(strcmp(buf, commands[i]) == 0)
                {
                    
                    system(exec);
                    flag=0;
                    break;
                }
            }

            if(flag)
            {
                printf("Command '%s' not supported", buf);
            }
            
        }

    }

    return 1;
}