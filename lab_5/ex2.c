#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int     fd[2];
  ssize_t size;
  char     string[] = "Hello, world!";
  char  resstring[14];

  if (pipe(fd) < 0) {
    printf("Pipe didnt open\n");
    exit(-1);
  }

  size = write(fd[1], string, 14);

  if (size != 14) {
    printf("Pipe didnt write all string\n");
    exit(-1);
  }

  size = read(fd[0], resstring, 14);

  if (size < 0) {
    printf("Pipe didnt read string\n");
    exit(-1);
  }

  printf("%s\n", resstring);

  if (close(fd[0]) < 0) {
    printf("Pipe didnt close reading side\n"); 
    exit(-1);
  }
  if (close(fd[1]) < 0) {
    printf("Pipe didnt close writing side\n"); 
    exit(-1);
  }

  return 0;
}
