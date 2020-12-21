#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include<string.h>

// pass the arguments as ./a.out filename num-bytes char_to_append x <- (x if you want to append atomically)
int main(int argc,char *argv[])
{
    int fd;
    mode_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    
    if(argc>5)
        exit(EXIT_FAILURE);

    int num_bytes = atoll(argv[2]);
    if(argc==5 && strcmp(argv[4],"x")==0)
    {
        fd = open(argv[1],O_APPEND|O_WRONLY,filePerms);
        while(num_bytes--)
        {
            write(fd,argv[3],1);
        }
    }
    else
    {
        fd = open(argv[1],O_WRONLY,filePerms);
        while(num_bytes--)
        {
            lseek(fd,0,SEEK_END);
            write(fd,argv[3],1);
        }
        
    }


    exit(EXIT_SUCCESS);

}