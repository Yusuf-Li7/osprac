#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main()
{
    int shmid;
    char pathname[] = "print.c";
    key_t key;
    char *code;
    
    int size = 0;
    int *size_ptr;
    
    if ((key = ftok(pathname,0)) < 0) {
        printf("Cant generate key\n");
        exit(-1);
    }
    
    if ((shmid = shmget(key, sizeof(int) + size * sizeof(char), 0)) < 0) {
        printf("Cant create shared memory\n");
        exit(-1);
    }
    if ((size_ptr = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
        printf("Cant attach shared memory\n");
        exit(-1);
    }
    size = *size_ptr;
    code = (char*)(size_ptr + 1);
    
    for (int i = 0; i < size; i++)
        putchar(code[i]);
    
    if (shmdt(size_ptr) < 0) {
        printf("Cant detach shared memory\n");
        exit(-1);
    }
    
    if (shmctl(shmid, IPC_RMID, NULL) < 0) {
        printf("Cant delete shared memory\n");
        exit(-1);
    }
    return 0;
}
