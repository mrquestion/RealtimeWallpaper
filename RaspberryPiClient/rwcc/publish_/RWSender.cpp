#include "RWSender.hpp"

#define log(x) printf(#x": %d\n",x)

int main(int argc, char *args[]) {
	puts("[RWSender] Start");

	if (argc == 2) {
		puts(args[1]);

		JSocket *js = new JSocket(RW_HOST, RW_PORT);

		js->write(RW_CLIENT);

		js->write(strlen(args[1]));
		js->write(args[1]);

		char filename[50];
		sprintf(filename, "%s/%s", FILE_PATH, args[1]);
		FILE *fro = fopen(filename, "rb");

		fseek(fro, 0, SEEK_END);
		int size = ftell(fro);
		log(size);
		byte *buffer = new byte[size];

		fseek(fro, 0, SEEK_SET);
		fread(buffer, size, 1, fro);

		char *cp = (char *)&size;

		int i, max;
		for (i=0, max=sizeof(int); i<max; i++) {
			js->write(*(cp++));
		}

		int count=0;
		for(i=0;i<size;i++)if(buffer[i]==0)count++;
		log(count);

		js->write(buffer, 0, size);

		delete buffer;

		fclose(fro);

		js->close();

		delete js;
	}
	else error("[RWSender] Invalid arguments.");

	puts("[RWSender] End");

	exit(EXIT_SUCCESS);
}

void error(const char *s) {
	fprintf(stderr, "Error: %s\n", s);
	exit(EXIT_FAILURE);
}
