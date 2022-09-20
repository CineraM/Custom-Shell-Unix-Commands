#include <dirent.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define FILE_LEN 20
#define ARR_LEN 99172

int main(int argc, char *argv[]) 
{

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

    for(i=0; i<idx; i++) printf("%s  ", files[i]);
    
    return(0);
}