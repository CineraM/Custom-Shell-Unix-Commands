#include <dirent.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILE_LEN 20
#define ARR_LEN 99172

int main(int argc, char *argv[]) 
{
    int param_size = argc - 1;

    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    char* temp;
    int i, j, idx = 0;

    static char files[ARR_LEN][FILE_LEN];

    // loop through the current directory
    if(d)
    {
        while((dir = readdir(d)) != NULL) 
        {
            // store regular files and directory names
            if(dir->d_type == DT_REG
            || dir->d_type == DT_DIR)
            {
                if(dir->d_name[0] != '.')
                {
                    strcpy(files[idx], dir->d_name);
                    idx++;
                }  
                
            }
        }
        closedir(d);
    }

    // sort LS output
    for(i=0; i<idx; i++)
    {
        for(j=i+1; j<idx; j++)
        {
            if(strcmp(files[j], files[i]) < 0)
            {
                char temp[FILE_LEN]; 
                strcpy(temp, files[i]);
                strcpy(files[i], files[j]);
                strcpy(files[j], temp);
            }
        }
    }

    // ls < test a
    if(param_size == 3)
    {

        if(strcmp(argv[3], "d") == 0)
        {
            if (access(argv[2], F_OK) == 0) 
            {
                if(remove(argv[2]) == 0) printf("deteled");
            }
        }

        FILE * fPtr;
        fPtr = fopen(argv[2], "w");

        if(fPtr == NULL)
        {
            printf("Unable to create file.\n");
            exit(EXIT_FAILURE);
        }
        
        char space[6] = "\n";
        for(i=0; i<idx; i++)
        {
            fputs(files[i], fPtr);
            fputs(space, fPtr);
        }

        fclose(fPtr);
    }
    else if(param_size == 0)
    {
        for(i=0; i<idx; i++) printf("%s  ", files[i]);
        printf("\n");
    }
    else
    {
        printf("Error: wrong args \n");
    }
    
    return(0);
}