#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define log(x) printf(#x": %d\n",x)
#define logh(x) printf(#x": 0x%08x\n",x)

typedef struct {
	int a;
	char c;
} A;

int main(int argc, char **args) {
	puts("bb");
	/*	log(argc);
	log(args[0]);
	puts(args[0]);
	log(atoi(args[0]));*/
	logh(args);
	puts(args[0]);
	logh(args[0]);
	log(**args);
	puts("write b");
	char c = 'i';
	write(args[0][0], &c, 1);
	puts("bb end");
	close(args[0][0]);
	int i;
	char *p = args[1];
	puts(p);
	log(atoi(p));
	logh(atoi(p));
	for(i=0,printf("hex:");i<8;printf(" %d",*(p+i++)));puts("");
	A *a = (A *)atoi(args[1]);
	log(a->a);
	printf("a->c: %d, %c\n", a->c, a->c);

	exit(0);
}
