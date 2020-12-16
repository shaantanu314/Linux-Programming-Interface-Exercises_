#include <sys/stat.h>
#include <fcntl.h>
#include "../header_files_from_book/tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc,char *argv[])
{
    int input_fd,output_fd,openFlags;
    char buf[BUF_SIZE];
    mode_t filePerms;
    ssize_t numRead;

    if(argc!=3)
    errExit("%s old-file new-file\n", argv[0]);

    input_fd = open(argv[1],O_RDONLY);
    if(input_fd == -1)
        errExit("opening file %s", argv[1]);
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    output_fd = open(argv[2],openFlags,filePerms);
    if(input_fd == -1)
        errExit("opening file %s", argv[2]);

    while((numRead = read(input_fd,buf,BUF_SIZE))>0)
        if(write(output_fd,buf,numRead)!=numRead)
            errExit("couldn't write completely");
    
    if(numRead == -1)
        errExit("read");

    if (close(input_fd) == -1)
        errExit("close input");
    if (close(output_fd) == -1)
        errExit("close output");

    exit(EXIT_SUCCESS);


}