#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define log(x) printf(#x": %d\n",x)
#define logh(x) printf(#x": 0x%08x\n",x)

typedef unsigned char byte;

int main(int argc, char *args[]) {
	int i = 0x12345678;
	logh(i);
	byte *cp = (byte *)&i;
	logh(&i);
	logh(cp);
	logh(*cp); logh(*(cp+1)); logh(*(cp+2)); logh(*(cp+3));
	//byte s[4] = { *(cp+0), *(cp+1), *(cp+2), *(cp+3) };
	byte *s = new byte[sizeof(int)];
	s[0] = cp[0];
	s[1] = cp[1];
	s[2] = cp[2];
	s[3] = cp[3];
	int *ip = (int *)s;
	logh(*ip);
	exit(EXIT_SUCCESS);
}
