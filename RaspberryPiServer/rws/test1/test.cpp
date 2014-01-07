#include "test.hpp"

int main(int argc, char *args[]) {
	//JSocket *js = new JSocket("127.0.0.1", 80);
	JSocket *js = new JSocket();
	int result = js->connect("127.0.0.1", 9123);
	printf("result: %d\n", result);
	puts(js->getHostName());
	puts("=================hi===============");
	int i, r;
	r=js->write("GET / HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");
	printf("r:%d\n",r);
	js->flush();
	puts("send");
	for (i=0; i<100; i++) {
		r = js->read();
		if (r <= 0) break;
		putchar(r);
	}
	puts("");
	puts("=================end==================");
	js->close();
	delete js;
	exit(EXIT_SUCCESS);
}
