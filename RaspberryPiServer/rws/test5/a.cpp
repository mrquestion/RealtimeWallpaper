#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "JFile.hpp"

#define log(x) printf(#x": %d\n",x)
#define logo(x) printf(#x": %o\n",x)

int main(int argc, char *args[]) {
	JFile *jf = new JFile("a.txt");
	log(jf->size());
	log(jf->isFile());
	log(jf->isDirectory());
	delete jf;
	jf = new JFile("b.txt");
	log(jf->create());
	log(jf->rename("bb.txt"));
	//log(jf->remove());
	delete jf;
	jf = new JFile(".");
	log(jf->size());
	log(jf->isFile());
	log(jf->isDirectory());
	log(jf->remove());
	delete jf;

	/*
	struct stat status;
	log(stat("a.txt", &status));
	logo(status.st_mode);
	log(status.st_size);
	memset(&status, 0, sizeof(status));
	log(stat(".", &status));
	logo(status.st_mode);
	log(status.st_size);
	memset(&status, 0, sizeof(status));
	log(stat("c.cc", &status));
	logo(status.st_mode);
	log(status.st_size);

    log(access("a.txt", F_OK));
	log(access("c.cc", F_OK));
	log(access(".", F_OK));

	int i = 040644;
	log(i);
	logo(i);
	logo(S_IFDIR);
	logo(!!(i&S_IFDIR));
	*/

	exit(EXIT_SUCCESS);
}
