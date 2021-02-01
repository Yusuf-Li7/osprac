#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, const char * argv[]) {
    printf("My pid = %d, my ppid = %d\n", (int)getpid(), (int)getppid());
    return 0;
}
