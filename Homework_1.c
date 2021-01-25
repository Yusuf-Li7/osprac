#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("My uid = %d, my gid = %d\n", (int)getuid(), (int)getgid());
    return 0;
}
