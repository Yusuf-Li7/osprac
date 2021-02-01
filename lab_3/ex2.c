  
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, const char * argv[]) {
    pid_t pid = fork();
    if(pid == -1){
        printf("Error, not found");
    } else if (pid == 0){
        printf("Child pid = %d\n", (int)getpid());
    } else {
        printf("Parent pid = %d\n", (int)getpid());
    }
    return 0;
}
