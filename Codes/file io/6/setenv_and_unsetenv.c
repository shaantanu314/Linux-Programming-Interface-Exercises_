#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <memory.h>

extern char **environ;

int setenv(const char * name , const char * value , int overwrite )
{
    char* key = getenv(name);

    if(key == NULL || (key!=NULL && overwrite>0))
    {
        char* string = (char *)malloc(2+strlen(name)+strlen(value));
        char* equal_to = "=";
        strcpy(string,name);
        strcat(string,equal_to);
        strcat(string,value);
        putenv(string);
    }
    return 0;
}

int unsetenv(const char * name )
{
    char* key = (char*)malloc(strlen(name));
    strcpy(key,name);
    return putenv(key);
}

int main()
{
    char **ep;
    setenv("shaantanu","good",1);
    printf("shaantanu=%s \n",getenv("shaantanu"));
    printf("%d\n",unsetenv("shaantanu"));
    printf("shaantanu=%s \n",getenv("shaantanu"));

    // link to another solution to this question without using putenv and getenv
    // using pointers only
    // https://github.com/posborne/linux-programming-interface-exercises/blob/master/06-processes/myenviron.c
    
}