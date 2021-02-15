#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  int fd;
  size_t size;

  (void)umask(0);

  if ((fd = open("myfile", O_RDONLY)) < 0) {
    printf("Error, File didnt open\n");
    printf("Exit");
    exit(-1);
  }

  char string[14];
  size = read(fd, string, 14);
  if (size != 14) {
    printf("size != 14");
    printf("Error, didnt read all string\n");
    printf("Exit");
    exit(-1);
  }

  printf("%s\n", string);

  if (close(fd) < 0)
    printf("fd close < 0");
    printf("File didnt close\n");
  return 0;
}
