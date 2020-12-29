#include <unistd.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>

ssize_t my_writev(int fd , const struct iovec *iov,int iovcnt)
{
    int total_bytes_written = 0;
    struct iovec *vec;
    for(int i=0;i<iovcnt;i++)
    {
        vec = (struct iovec *)&iov[i];
        int bytes_written = write(fd,  vec->iov_base , vec->iov_len );
        if(bytes_written<0)
        {
            return total_bytes_written;
        }
        if(bytes_written<vec->iov_len)
            return total_bytes_written;
        total_bytes_written+=bytes_written;

    }
    return total_bytes_written;
}

ssize_t my_readv(int fd , const struct iovec *iov , int iovcnt)
{
    int total_bytes_read = 0;
    struct iovec *vec;
    char *buf[16];
    for(int i=0;i<iovcnt;i++)
    {
        vec = (struct iovec *)&iov[i];
        // printf("%s \n",vec->iov_base);
        int bytes_read = read(fd,  vec->iov_base, vec->iov_len);
        if(bytes_read<0)
        {
            return total_bytes_read;
        }
        if(bytes_read<vec->iov_len)
            return total_bytes_read;
        total_bytes_read+=bytes_read;

    }
    return total_bytes_read;
}

#define NUMVECS 20
#define CHUNKSIZE 16

static struct iovec iovecs[NUMVECS];


int main(int argc , char* argv[])
{
    

    int input_fd  = open(argv[1],O_RDONLY,S_IRUSR|S_IWUSR);
    int output_fd = open(argv[2],O_WRONLY,S_IRUSR|S_IWUSR);

    for(int i=0;i<NUMVECS;i++)
    {
        void * mem;

		mem = malloc(CHUNKSIZE);
		memset(mem, 0, CHUNKSIZE);
		iovecs[i].iov_base = mem;
		iovecs[i].iov_len = CHUNKSIZE;

    }

    int total_bytes_read = my_readv(input_fd,&iovecs[0],NUMVECS);
    printf("%d",total_bytes_read);
    my_writev(output_fd,&iovecs[0],NUMVECS);





}