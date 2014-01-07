#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <sys/socket.h>

int main() {
	int s = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in a, b;

	a.sin_family = AF_INET;
	a.sin_addr.s_addr = htonl(INADDR_ANY);
	a.sin_port = htons(9123);

	printf("bind: %d\n", bind(s, (struct sockaddr *)&a, sizeof(a)));
	printf("listen: %d\n", listen(s, 5));

	int size = sizeof(b);
	int c = accept(s, (struct sockaddr *)&b, &size);
	puts("accept");

	int r, d;
	//while ((r=read(c, &d, 1)) > 0) printf("%d: %c\n", d, d);
	char msg1[20];
	r = read(c, msg1, sizeof(msg1));
	msg1[r] = 0;
	puts(msg1);
	char msg2[20] = "hi client";
	write(c, msg2, strlen(msg2));

	close(c);
	close(s);

	puts("end");

	exit(0);
}
