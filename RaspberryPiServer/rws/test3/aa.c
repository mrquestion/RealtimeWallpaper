#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define log(x) printf(#x": %d\n",x)
#define logh(x) printf(#x": 0x%08x\n",x)

typedef struct {
	int a;
	char c;
} A;

int main() {
	puts("aa");
	int a = open("a.txt", O_WRONLY | O_CREAT | O_TRUNC);
	logh(&a);
	puts("write a");
	char c = 'h';
	write(a, &c, 1);
	A aa = { 3456, 'R' };
	char *p = (char *)&aa;
	log(&aa);
	logh(&aa);
	int i;
	for(i=0,printf("hex:");i<8;printf(" %d",*(p+i++)));puts("");
	char bf[20];
	sprintf(bf, "%d", p);
	//	for(i=0;i<8;bf[i]=*(p+i),i++);
	char *v[] = { (char *)&a, bf, NULL };
	//	log(execl("bb", (char *)&a, (char *)&aa, NULL));
	log(execv("bb", v));
	puts("aa end");
	close(a);
	exit(0);
}
