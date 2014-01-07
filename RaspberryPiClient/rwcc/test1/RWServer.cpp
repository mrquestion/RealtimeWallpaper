#include "RWServer.hpp"

int main(int argc, char *args[]) {
	JServerSocket *jss = new JServerSocket(80);
	int i, r;
	for (i=0; i<10; i++) {
		printf("wait client %d...\n", i);
		JSocket *js = jss->accept();
		printf("accepted: %s\n", js->getHostName());
		puts("==== hi ====");
		while (true) {
			r = js->read();
			if (r <= 0) break;
			putchar(r);
		}
		puts("");
		js->write("hi ");
		js->write(i+48);
		js->flush();
		puts("==== bye ===");
		js->close();
		puts("disconnected");
		delete js;
	}
	jss->close();
	delete jss;
	exit(EXIT_SUCCESS);
}
