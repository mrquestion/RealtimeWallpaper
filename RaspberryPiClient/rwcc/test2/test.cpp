#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *args[]) {
	time_t now;
	struct tm *nowtm;
	char filename[50];
	char command[100];
	int i;
	for (i=0; i<10; i++) {
		time(&now);
		nowtm = localtime(&now);
		strftime(filename, sizeof(filename), "%Y%m%d_%H%M%S", nowtm);
		sprintf(command, "raspistill -o %s.jpg", filename);
		puts(command);
		system(command);

		puts("sleep 1 sec...");
		sleep(1);
	}
	exit(EXIT_SUCCESS);
}
