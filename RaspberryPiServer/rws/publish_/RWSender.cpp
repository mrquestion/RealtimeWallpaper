#include "RWSender.hpp"

#define log(x) printf(#x": %d\n",x)
//#define logh(x) printf(#x": 0x%08x\n",x)

int main(int argc, char *args[]) {
	puts("[RWSender] Start");

	if (argc == 2) {
		//puts(args[1]);
		struct sockaddr_in a;
		JSocket *js = new JSocket(atoi(args[1]), a);

		char filename[50];
		sprintf(filename, "%s/%s", FILE_PATH, FILE_LATEST);
		FILE *fro = fopen(filename, "rb");

		fseek(fro, 0, SEEK_END);
		int size = ftell(fro);
		log(size);
		fseek(fro, 0, SEEK_SET);

		//puts("before new buffer");
		byte *buffer = new byte[size];
		fread(buffer, size, 1, fro);
		//puts("read image");
		fclose(fro);

		char *cp = (char *)&size;
		int i, max;
		for (i=0, max=sizeof(int); i<max; i++) {
			//log(*cp);
			js->write(*(cp++));
		}
		puts("send size");

		js->write(buffer, 0, size);
		//puts("send data");

		delete [] buffer;

		//puts("read result");
		int result = js->read();
		if (result == SEND_SUCCESS) puts("\tSend success.");
		else if (result == SEND_FAILURE) puts("\tSend fail.");
		else error("RWSender: Invalid flag data received.");

		js->close();
		delete js;
	}
	else error("RWSender: Invalid arguments.");

	puts("[RWSender] End");

	exit(EXIT_SUCCESS);
}

void error(const char *s) {
	fprintf(stderr, "Error: %s\n", s);
	exit(EXIT_FAILURE);
}
