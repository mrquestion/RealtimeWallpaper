#include "RWReceiver.hpp"

#define log(x) printf(#x": %d\n",x)
#define logh(x) printf(#x": 0x%08x\n",x)

int main(int argc, char *args[]) {
	puts("[RWReceiver] Start");

	if (argc == 2) {
		mkdir(FILE_PATH, 0755);

		struct sockaddr_in a;
		JSocket *js = new JSocket(atoi(args[1]), a);

		int length = js->read();
		//printf("length: %d\n", length);
		if (length > 0) {
			JBuffer *jb = new JBuffer();

			jb->setSize(length);
			js->read(*jb);

			byte *buffer = jb->getBytes();
			char *s = new char[length+1];
			strcpy(s, (char *)buffer);
			delete [] buffer;

			char filename[50];
			sprintf(filename, "%s/%s", FILE_PATH, s);
			delete [] s;
			//puts(filename);
			FILE *fwo = fopen(filename, "wb");

			jb->setSize(sizeof(int));
			js->read(*jb);

			buffer = jb->getBytes();

			//int i;
			//for(i=0;i<sizeof(int);i++)logh(buffer[i]);

			int *ip = (int *)buffer;
			int size = *ip;
			//log(size);
			delete [] buffer;

			delete jb;

			int r, count = size;
			while (true) {
				jb = new JBuffer(count);
				//jb->setSize(size);
				//jb->clear();
				r = js->read(*jb);
				if (r < 0) error("RWReceiver: Invalid data received.");
				jb->setSize(r);
				//log(r);

				buffer = jb->getBytes();
				fwrite(buffer, r, 1, fwo);
				delete [] buffer;
				delete jb;

				if (r < count) count -= r;
				else break;
			}

			/*
			jb->setSize(size);
			int r = js->read(*jb);
			log(r);

			buffer = jb->getBytes();
			fwrite(buffer, size, 1, fwo);
			delete buffer;
			*/

			fclose(fwo);

			FILE *fro = fopen(filename, "rb");

			char latest[50];
			sprintf(latest, "%s/%s", FILE_PATH, FILE_LATEST);
			fwo = fopen(latest, "wb");

			buffer = new byte[size];

			fread(buffer, size, 1, fro);
			fwrite(buffer, size, 1, fwo);

			delete [] buffer;

			fclose(fro);
			fclose(fwo);
		}
		else error("RWReceiver: Invalid length data received.");

		delete js;
	}
	else error("RWReceiver: Invalid arguments.");

	puts("[RWReceiver] End");

	exit(EXIT_SUCCESS);
}

void error(const char *s) {
	fprintf(stderr, "Error: %s\n", s);
	exit(EXIT_FAILURE);
}
