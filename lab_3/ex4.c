#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[], char* envp[])
{
  pid_t pid = fork();
    if(pid == -1){
        printf("Error");
    } else if (pid == 0){
        printf("Child pid = %d\n", (int)getpid());
        (void)execle("/bin/cat", "/bin/cat", "Hello,", "world!", 0, envp);
    } else {
        printf("Parent pid = %d\n", (int)getpid());
    }
 
  return 0;
}
