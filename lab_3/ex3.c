#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char* argv[], char *envp[]) {
	
  printf("Information about argument line:\n");
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}
	
	printf("Information about environment:\n");
	int i = 0;
	while (envp[i] != NULL) {
		printf("%s\n", envp[i++]);
	}
  
	return 0;
}
