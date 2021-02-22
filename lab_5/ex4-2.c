#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd;
  size_t size;
 
  char name[] = "/tmp/aaa.fifo";

  (void)umask(0);

  printf("IMPORTANT: fifo is created in /tmp/aaa.fifo because "
         "it didn't work on my laptop's wsl otherwise\n");

  if (mknod(name, S_IFIFO | 0666, 0) < 0) {
    printf("Can\'t create FIFO\n");
    exit(-1);
  }

  if ((fd = open(name, O_WRONLY)) < 0) {
    printf("Can\'t open FIFO for writing\n");
    exit(-1);
  }

  size = write(fd, "Hello, world!", 14);

  if (size != 14) {
    printf("Can\'t write all string to FIFO\n");
    exit(-1);
  }

  if (close(fd) < 0) {
    printf("Can\'t close FIFO\n");
    exit(-1);
  }

  printf("Writer exits, message is written\n");

  return 0;
}
