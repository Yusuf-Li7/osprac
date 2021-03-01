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
    char *source_code;
    
    int size = 0;
    int *size_ptr;
    FILE *file;
    file = fopen(pathname, "r");
    
    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    rewind(file);
    
    if ((key = ftok(pathname,0)) < 0) {
        printf("Cant generate key\n");
        exit(-1);
    }
    
    if ((shmid = shmget(key, sizeof(int) + size * sizeof(char), 0666|IPC_CREAT)) < 0) {
        printf("Cant create shared memory\n");
        exit(-1);
    }
    if ((size_ptr = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
        printf("Cant attach shared memory\n");
        exit(-1);
    }
    *size_ptr = size;
    source_code = (char*)(size_ptr + 1);
    
    for (int i = 0; i < size; i++)
        source_code[i] = fgetc(file);
        
    fclose(file);
        
    
    if (shmdt(size_ptr) < 0) {
        printf("Cant detach shared memory\n");
        exit(-1);
    }
    return 0;
}
