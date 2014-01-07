#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define log(x) printf(#x": %d\n",x)

int main(int argc, char *args[]) {
	puts("process B");
	int i = 0;
	for (i=0;i<argc;log(i),puts(args[i++]));

	char msg[20] = "hi server";
	int s = atoi(args[0]);
	write(s, msg, strlen(msg));
	puts("write");
	int r = read(s, msg, sizeof(msg));
	msg[r] = 0;
	puts("read");
	puts(msg);
	puts("end");

	exit(EXIT_SUCCESS);
}
