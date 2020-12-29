#include <sys/stat.h>
#include <fcntl.h>
#include "../header_files_from_book/tlpi_hdr.h"

#define MAX_LEN 1024
int main(int argc,char *argv[])
{
    mode_t filePerms;
    ssize_t numRead;
    char buf[MAX_LEN];
    int output_fd ;
    if(argc>3)
    {
        errExit("%s -a filename", argv[0]);
    }
    // write(STDOUT_FILENO,argv[1],strlen(argv[1]));

    if(argc==3 && strcmp(argv[1],"-a")==0)
    {
        output_fd = open(argv[2],O_WRONLY|O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |S_IROTH | S_IWOTH);
        
        if(output_fd==-1)
        {
            errExit("open");
        }
    }
    while(TRUE)
    {
        numRead = read(STDIN_FILENO,buf,MAX_LEN);
        if(numRead==0)
        {
            // CTRL + D is EOF and it closes STDIN
            exit(EXIT_SUCCESS);
        }
        if(numRead == -1)
        {
            errExit("read");
        }
        if(argc==1)
        {
            if(write(STDOUT_FILENO,buf,numRead)!=numRead)
            {
                errExit("write");
            }
        }
        if(strcmp(argv[1],"-a")==0)
        {
        
            if(write(output_fd,buf,numRead)!=numRead)
            {
                errExit("write");
            }
        }
    }
    

    exit(EXIT_SUCCESS);


}