#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    int fd = open(argv[1],O_RDWR|O_APPEND,S_IRUSR|S_IWUSR);

    int dup_fd = dup(fd);

    int flags = fcntl(fd,F_GETFL);
    printf("flags for original : %d\n",flags);
    flags = fcntl(dup_fd,F_GETFL);
    printf("flags for dulpicate : %d\n",flags);


    off_t offset = lseek(fd,10,SEEK_CUR);
    printf("flags for original : %ld\n",offset);
    offset = lseek(fd,0,SEEK_CUR);
    printf("flags for dulpicate : %ld\n",offset);




    close(fd);
    close(dup_fd);




}