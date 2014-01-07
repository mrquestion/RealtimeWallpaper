#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define log(x) printf(#x": %d\n",x)

int main(int argc, char *args[]) {
	puts("process A");
	int pid = fork();
	log(pid);

	if (pid < 0) puts("error");
	else if (pid > 0) {
		puts("parent wait");
		int resultp = wait(pid);
		log(resultp);
	}
	else {
		puts("child");
		//char a[20], b[20], c[20], d[20];
		//sprintf(a, "%d", pid);
		//sprintf(b, "%d", getpid());
		//sprintf(c, "%d", getppid());

		int s = socket(PF_INET, SOCK_STREAM, 0);
		log(s);

		struct sockaddr_in a;
		memset(&a, 0, sizeof(a));
		a.sin_family = AF_INET;
		a.sin_addr.s_addr = inet_addr("127.0.0.1");
		a.sin_port = htons(9123);

		puts("before connect");
		int r = connect(s, (struct sockaddr *)&a, sizeof(a));
		log(r);
		puts("after connect");

		//char b[9];
		//sprintf(b, "%d", s);
		//execl("b", b, NULL);
		execl("b", itoa(s), NULL);
		//sprintf(d, "%d", s);
		//int resultc = execl("a", a, b, c, d, NULL);
		//log(resultc);
	}

	if (pid > 0) puts("parent end");
	else if (pid == 0) puts("child end: this message never show");
	
	exit(EXIT_SUCCESS);
}
