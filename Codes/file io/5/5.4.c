#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int my_dup(int oldfd)
{
    return fcntl(oldfd,F_DUPFD,0);
}
int my_dup2(int oldfd,int newfd)
{
    if(fcntl(oldfd,F_GETFL)==-1)
    {
        errno = EBADF;
        return -1;
    }
    if(oldfd==newfd)
    {
        return oldfd;
    }
    else
    {
        close(newfd);
        return fcntl(oldfd,F_DUPFD,newfd);
    }

}

int main(int argc, char* argv[])
{
    int fd = open(argv[1],O_RDWR,S_IRUSR|S_IWUSR);

    int dup_fd = my_dup(fd);
    printf("old fd is : %d and new fd is :%d",fd,dup_fd);

    int dup2_fd = my_dup2(fd,5);
    printf("old fd is : %d and new fd is :%d",fd,dup_fd);
    close(fd);
    close(dup2_fd);
    close(dup_fd);



}