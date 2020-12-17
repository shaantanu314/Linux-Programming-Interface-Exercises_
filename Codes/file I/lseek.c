#include <sys/stat.h>
#include <fcntl.h>
#include "../header_files_from_book/tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int fd,len,numRead;
    off_t offset;
    char *ptr,*buf;
    char *str ;

    if(argc!=4)
    {
        errExit("%s filepath 's'offset 'r/R'length/'w'str\n", argv[0]);
    }

    fd = open(argv[1],O_RDWR|O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |S_IROTH | S_IWOTH);
    if(fd==-1)
        errExit("open");

    if(argv[2][0]!='s')
        errExit("wrong-format");
    offset    = strtol(&argv[2][1],&ptr,10);
    if(lseek(fd,offset,SEEK_SET) == -1)
        errExit("lseek");
    printf("%s : seek succeeded\n",argv[2]);

    char mode = argv[3][0];
    printf("mode : %c\n",mode);
    if(mode!='r' && mode!='R' && mode!='w')
        errExit("invalid-parameters");
    
    switch(mode){
        case 'r':
        case 'R':
            len = strtol(&argv[3][1],&ptr,10);
            buf = malloc(len);
            if(buf == NULL)
                errExit("malloc");
            numRead = read(fd,buf,len);
            if (numRead == -1)
                errExit("read");
            if (numRead == 0)
                printf("%s: end-of-file\n", argv[2]);
            else
            {
                for(int i=0;i<numRead;i++)
                {
                    if(mode == 'r')
                    {
                        printf("%c",isprint((unsigned char)buf[i])?buf[i]:'?');
                    }
                    else
                    {
                        printf("%x",(unsigned char)buf[i]);
                    }
                    
                }
            }
            
            printf("\n");
            break;
        
        case 'w':
            str = &argv[3][1];
            int str_len = strlen(str);
            if(write(fd,str,str_len)!=str_len)
                errExit("write");
            printf("%s : wrote %ld bytes \n",argv[3],str_len);
            break;
        
    }
    exit(EXIT_SUCCESS);

}