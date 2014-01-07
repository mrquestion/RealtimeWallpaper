#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(int argc, char *args[]) {
	puts("process A");
	printf("%d %s %s %s %s\n", argc, args[0], args[1], args[2], args[3]);
	int s = atoi(args[3]);
	char c = 'h';
	write(s, &c, 1);
	c = 'i';
	write(s, &c, 1);
	close(s);
	exit(EXIT_SUCCESS);
}
