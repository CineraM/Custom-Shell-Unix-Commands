// sed 's/Sunday/Sunday is holiday/' weekday.txt
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUF_LEN 100

// GEEKS FOR GEEKS FUNCTION
// https://www.geeksforgeeks.org/c-program-replace-word-text-another-given-word/
void replaceWord(const char* s, const char* oldW, const char* newW)
{
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
 
    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;
            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }
    // Making new string of enough length
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
 
    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }
    result[i] = '\0';
    printf("%s", result);
}



// fix args
int main(int argc, char *argv[])
{
    FILE *fptr;
    int param_size = argc - 1;

    char buf[BUF_LEN];
    char compare[BUF_LEN];
    char replace[BUF_LEN];

    // 's/find/replace/'
    //  sed default args ^

    int i=2;
    int j=0;

    while(1)
    {
        if(argv[1][i]=='/')
        {
            i++;
            break;
        }
        compare[j]=argv[1][i];
        j++;
        i++;
    }
    compare[j+1] = '\0';
    
    j=0;
    while(1)
    {
        if(argv[1][i]=='/')
        {
            i++;
            break;
        }
        replace[j]=argv[1][i];
        j++;
        i++;
    }
    replace[j+1] = '\0';

    
    fptr = fopen(argv[2], "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    
    while(fgets(buf, BUF_LEN, fptr)) 
    {
        // call fnc and replace
        if(strstr(buf, compare) != NULL)
        {
            replaceWord(buf, compare, replace);
        }
        else
        {
            printf("%s", buf);
        } 
    }
    fclose(fptr);

    return 0;
}
