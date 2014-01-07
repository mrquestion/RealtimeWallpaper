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
	a.sin_addr.s_addr = inet_addr("127.0.0.1");//htonl(INADDR_ANY);
	a.sin_port = htons(9123);
	//printf("bind: %d\n", bind(s, (struct sockaddr *)&a, sizeof(a)));
	//printf("listen: %d\n", listen(s, 5));
	//int size = sizeof(b);
	//int c = accept(s, (struct sockaddr *)&b, &size);
	//puts("accept");
	//int r, d;
	int r = connect(s, (struct sockaddr *)&a, sizeof(a));
	printf("connect: %d\n", r);
	puts("connect");
	//while ((r=read(s, &d, 1)) > 0) printf("%d\n", d);
	char c = 1;
	r = write(s, &c, 1);
	printf("write: %d\n", r);
	close(s);
	puts("end");
	exit(0);
}
