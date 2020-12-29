#include <setjmp.h>
#include <stdio.h>

static jmp_buf env;

int function(char* str)
{
    if(setjmp(env)==0)
    {
        printf("none\n");
    }
    else
    {
        printf("%s\n",str);
    }
    return 0;
}

int main()
{
    function("1");

    longjmp(env,1);
    // this will lead to segmentation fault

}