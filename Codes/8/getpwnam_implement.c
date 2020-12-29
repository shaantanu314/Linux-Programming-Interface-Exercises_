
#define _DEFAULT_SOURCE
#define _BSD_SOURCE

#include <pwd.h>
#include <stdio.h>
#include <string.h>

struct passwd *my_getpwnam(const char *name)
{
    struct passwd *pwd;
    while((pwd = getpwent())!=NULL)
    {
        if(strcmp(pwd->pw_name,name)==0)
            return pwd;

    }

    return NULL;
}

int main(int argc,char** argv)
{
    if(argc!=2)
    {
        printf("wrong format\n");
        return 1;
    }
    struct passwd *pwd = my_getpwnam(argv[1]);
    if(pwd!=NULL)
    {
        printf("  pw_name=\"%s\",\n", pwd->pw_name);
        printf("  pw_uid=%d,\n", pwd->pw_uid);
        printf("  pw_gid=%d,\n", pwd->pw_gid);
        printf("  pw_dir=\"%s\",\n", pwd->pw_dir);
        printf("  pw_shell=\"%s\"\n", pwd->pw_shell);
    }
    else
    {
        printf("NO entry found\n");
    }

    return 0;   
}