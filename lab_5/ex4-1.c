#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd;
  size_t size;
  char resstring[14];
  char name[] = "/tmp/aaa.fifo";

  (void)umask(0);

  /* Reader program */

  if ((fd = open(name, O_RDONLY)) < 0) {
    printf("Can\'t open FIFO for reading\n");
    exit(-1);
  }

  size = read(fd, resstring, 14);

  if (size < 0) {
    printf("Can\'t read string from FIFO\n");
    exit(-1);
  }

  printf("Reader exits, message is read: %s\n", resstring);

  if (close(fd) < 0) {
    printf("Can\'t close FIFO\n");
    exit(-1);
  }

  return 0;
}
