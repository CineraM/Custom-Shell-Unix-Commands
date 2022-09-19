#include <dirent.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) 
{

    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    char* temp;

    // loop through the current directory
    if(d)
    {
        while((dir = readdir(d)) != NULL) 
        {
            // store regular files and directory names
            if(dir->d_type == DT_DIR)
            {
                // if dir already exists, exit the program 
                if(strcmp(dir->d_name, argv[1])  == 0)
                {
                    printf("Error: %s already exists\n", argv[1]);
                    closedir(d);
                    exit(0);
                }  
                
            }
        }
        closedir(d);
    }

    mkdir(argv[1], 0777);
    printf("%s created\n", argv[1]);
    
    return(0);
}