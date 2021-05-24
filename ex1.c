#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void max_link_depth(int rec) {
	// For creating new files
	char previous_file_name[32];
	char current_file_name[32];

	// Create files
	sprintf(previous_file_name, "My_test%d", rec);
	sprintf(current_file_name, "My_test%d", rec + 1);

	if (symlink(previous_file_name, current_file_name) != 0) {
		printf("Error with creaing symlink, so terminating.\n");
		exit(-4);
	}
  
	rec = rec + 1;

	// Open current file. If the max depth was overflow, we are done with this exercise
	int file_desc;
	if ((file_desc = open(current_file_name, O_RDWR | O_CREAT, 0666)) < 0) {
		printf("Max recursive link depth reached. Creating more links is not possible.\n");
		printf("Result of recursive depth = %d\n", rec - 1);
		if (remove(current_file_name) < 0) {
			printf("Unable to remove a link. Terminating.\n");
			exit(-5);
		}
		return;
	}
  
	// Close opened file
	if (close(file_desc) < 0) {
		printf("Unable to close the file. Terminating.\n");
		exit(-3);
	}

	// Create different link
	max_link_depth(rec);
	
  
	if (remove(current_file_name) < 0) {
		printf("Unable to remove a link. Terminating.\n");
		exit(-5);
	}
}

void check(char file_name[], int file_desc) {
	// Open a file or create one
	if ((file_desc = open(file_name, O_RDWR | O_CREAT, 0666)) < 0) {
		printf("We cant open the file, so Terminating.\n");
		exit(-1);
	}
  
	// We close opened regular file
	if (close(file_desc) < 0) {
		printf("We cant close the file.\n");
		exit(-2);
	}  
}

void check_2(char file_name[]) {
  if (remove(file_name) < 0) {
		printf("We cant remove initial file, so Terminating.\n");
		exit(-6);
	}
}

int main() {
	char file_name[] = "My_test";
	int file_desc;

  check(file_name, file_desc);
	max_link_depth(0);
  check_2(file_name);

	return 0;
}
