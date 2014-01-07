#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define log(x) printf(#x": %d\n",x)

typedef struct sockaddr_in sain;
typedef struct sockaddr sa;

void error(const char *);

int main(int argc, char *args[]) {
	int ss, sc;
	sain as, ac;
	int acs = sizeof(ac);;

	ss = socket(2, 1, 0);
	if (ss < 0) error("socket()");
	else puts("*** socket created");

	memset(&as, 0, sizeof(as));
	as.sin_family = 2;
	as.sin_addr.s_addr = htonl(0);
	as.sin_port  = htons(9090);

	if (bind(ss, (sa *)&as, sizeof(as)) < 0) error("bind()");
	else puts("*** bind success");

	if (listen(ss, 1) < 0) error("listen()");
	else puts("*** start listen");

	char c, buffer[1024];
	int i, j, r, count = 1, crlf = 0;
	while (1) {
		printf("*** wait client: %d\n", count);
		sc = accept(ss, (sa *)&ac, &acs);
		if (sc < 0) error("accept()");
		else {
			puts("*** client accepted");
			count++;
		}

		for (i=0; i++<80; putchar('=')); puts("");
		puts(" CLIENT MESSAGE");
		while ((r=read(sc, &c, 1)) > 0) {
			putchar(c);

			if (c == 10) {
				if (crlf == 0) crlf++;
				else if (crlf == 2) crlf++;
			}
			else if (c == 13) {
				if (crlf == 1) crlf++;
				else crlf = 0;
			}
			else crlf = 0;

			if (crlf >= 3) break;
		}
		puts(" CLIENT MESSAGE END");
		for (i=0; i++<80; putchar('=')); puts("");


		close(sc);
		puts("*** close client socket");
	}

	close(ss);
	puts("*** close server socket");

	exit(0);
}

void error(const char *s) {
	fprintf(stderr,  "Error: %s\n", s);
	if (errno != 0) {
		fputc('\t', stderr);
		char buffer[1024];
		sprintf(buffer, "cat /usr/include/asm-generic/errno.h | grep -P '\t%d\t'", errno);
		system(buffer);
		
		exit(1);
	}
}
